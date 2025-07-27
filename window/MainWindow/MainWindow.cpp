#include <cstdint>
#include <d2d1.h>

#include "../../config/colors.hpp"
#include "../../config/font.hpp"

#include "./MainWindow.hpp"

template<class T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

void MainWindow::drawHero() const {
    uint32_t** pixels = this->hero->getPixels();

    int heroSize = this->hero->size;
    int x = this->hero->x * BLOCK + PADDING + (BLOCK - HERO_PIXEL_WIDTH) / 2;
    int y = this->hero->y * BLOCK + PADDING;

    for (size_t i = 0; i < HERO_PIXEL_HEIGHT; ++i) {
        for (size_t j = 0; j < HERO_PIXEL_WIDTH; ++j) {
            uint32_t color = pixels[i][j];
            if (color == 0x000000) color = GROUND;

            pBrush->SetColor(D2D1::ColorF(color));

            D2D1_RECT_F pixel = D2D1::Rect(
                x + j * heroSize,
                y + i * heroSize,
                x + j * heroSize + heroSize,
                y + i * heroSize + heroSize);
            
            pRenderTarget->FillRectangle(pixel, pBrush);
        }
    }
}

void MainWindow::drawMap() const {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (this->hero->map->getMap()[i][j] == 0) pBrush->SetColor(D2D1::ColorF(GROUND));
			if (this->hero->map->getMap()[i][j] == 1) pBrush->SetColor(D2D1::ColorF(WALL));

			int x = j * BLOCK + PADDING;
			int y = i * BLOCK + PADDING;

			D2D1_RECT_F block = D2D1::Rect(x, y, x + BLOCK, y + BLOCK);
			pRenderTarget->FillRectangle(block, pBrush);
		}
	}
}

void MainWindow::drawLoot() const {
    int lootSize = LOOT_SIZE;

    for (int l = 0; l < LOOT_COUNT; ++l) {
        Loot* loot = this->hero->map->loots[l];

        if (loot->looted) continue;

        uint32_t** pixels = loot->getPixels();

        int x = loot->x * BLOCK + PADDING;
        int y = loot->y * BLOCK + PADDING;
    
        for (int i = 0; i < LOOT_HEIGHT; ++i) {
            for (int j = 0; j < LOOT_WIDTH; ++j) {
                uint32_t color = pixels[i][j];
         
                if (color == 0x000000) color = GROUND;

                pBrush->SetColor(D2D1::ColorF(color));

                D2D1_RECT_F pixel = D2D1::Rect(
                    x + j * lootSize,
                    y + i * lootSize,
                    x + j * lootSize + lootSize,
                    y + i * lootSize + lootSize);
                
                pRenderTarget->FillRectangle(pixel, pBrush);
            }
        }
    }
}


void MainWindow::drawScore() const {

	D2D1_RECT_F textRect = D2D1::RectF(
		static_cast<FLOAT>(20),
		static_cast<FLOAT>(16 * BLOCK),
		static_cast<FLOAT>(20 + 16 * BLOCK),
		static_cast<FLOAT>(16 * BLOCK + BLOCK)
	);

	pBrush->SetColor(D2D1::ColorF(SCORE_COLOR));

	pRenderTarget->DrawText(
		L"SCORE: 0020",                       
	    11,               
		pTextFormat,                  
		textRect,                       
		pBrush                        
	);

}

MainWindow::MainWindow(const wchar_t* window_name, int x, int y, int width, int height, Hero* hero): 
    BaseWindow(window_name, x, y, width, height),
    pFactory(NULL),
    pRenderTarget(NULL),
    pBrush(NULL), 
    hero(hero) {};

PCWSTR MainWindow::className() const {
    return L"Main class window";
} 

HRESULT MainWindow::createGraphicsResources() {
    HRESULT hr = S_OK;

    if (pRenderTarget == NULL) {
        RECT client_rect;

        GetClientRect(m_hwnd, &client_rect);

        D2D1_SIZE_U size = D2D1::SizeU(client_rect.right, client_rect.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),

            &pRenderTarget);

		if (pDWriteFactory == NULL) {
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(IDWriteFactory),
				reinterpret_cast<IUnknown**>(&pDWriteFactory)
			);
		}

        Font font;

        hr = pDWriteFactory->CreateTextFormat(
            font.family,
            nullptr,
            font.weight,
            font.style,
            font.stretch,
            font.size,
            L"en-US",                
            &pTextFormat
        );

        if (SUCCEEDED(hr)) {
            const D2D1_COLOR_F color = D2D1::ColorF(0x0000000); //fix the color 
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
        }
    }
    
    return hr;
}

void MainWindow::discardGraphicsResources() {
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush); 
    SafeRelease(&pDWriteFactory);
    SafeRelease(&pTextFormat);
}

void MainWindow::onPaint() {
    HRESULT hr = createGraphicsResources();

    if (SUCCEEDED(hr)) {
        PAINTSTRUCT ps; 

        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue)); // select another color
    
        drawMap();
        drawLoot();
        drawHero();
        drawScore();

        hr = pRenderTarget->EndDraw();

        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
			discardGraphicsResources();
		}

		EndPaint(m_hwnd, &ps);
    }
}

void MainWindow::resize() {
	if (pRenderTarget != NULL) {
		RECT client_rect;
		GetClientRect(m_hwnd, &client_rect);

		D2D1_SIZE_U size = D2D1::SizeU(client_rect.right, client_rect.bottom);

		pRenderTarget->Resize(size);

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            if (FAILED(D2D1CreateFactory(
                D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
                    return -1;
            }
            // add map and hero initialization
        
            return 0;
        }
        case WM_DESTROY: {
            discardGraphicsResources();
            SafeRelease(&pFactory);
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT: {
            onPaint();
            return 0;
        }
        case WM_SIZE: {
            resize();
            return 0;
        }
        case WM_KEYDOWN: {
            this->hero->move(wParam);
            onPaint();
            return 0;
        }

    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}