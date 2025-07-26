#pragma once 
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>

#include "../BaseWindow/BaseWindow.hpp"

class MainWindow : public BaseWindow<MainWindow> {
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;

    ID2D1SolidColorBrush* pBrush;

    HRESULT createGraphicsResources();
    void discardGraphicsResources();
    void onPaint();
    void resize();

    public: 
        MainWindow(const wchar_t*, int, int, int, int);

        PCWSTR className() const;
        LRESULT handleMessage(UINT, WPARAM, LPARAM);
};