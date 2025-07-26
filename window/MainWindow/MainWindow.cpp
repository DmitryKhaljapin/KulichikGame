#include "./MainWindow.hpp"

template<class T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}


MainWindow::MainWindow(const wchar_t* window_name, int x, int y, int width, int height): 
    BaseWindow(window_name, x, y, width, height),
    pFactory(NULL),
    pRenderTarget(NULL),
    pBrush(NULL) {};

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
    // add other resourses;
}

void MainWindow::onPaint() {
    HRESULT hr = createGraphicsResources();

    if (SUCCEEDED(hr)) {
        PAINTSTRUCT ps; 

        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue)); // select another color
    
        //add draw map hero score;

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
            // implement later
            return 0;
        }

    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}