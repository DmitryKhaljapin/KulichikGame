#pragma once 
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>

#include "../BaseWindow/BaseWindow.hpp"
#include "../../Hero/Hero.hpp"

class MainWindow : public BaseWindow<MainWindow> {
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;

    ID2D1SolidColorBrush* pBrush;

    Hero* hero = 0;

    HRESULT createGraphicsResources();
    void discardGraphicsResources();
    void onPaint();
    void resize();

    void drawMap() const;
    void drawHero() const;
    void drawLoot() const;

    public: 
        MainWindow(const wchar_t*, int, int, int, int, Hero*);

        PCWSTR className() const;
        LRESULT handleMessage(UINT, WPARAM, LPARAM);
};