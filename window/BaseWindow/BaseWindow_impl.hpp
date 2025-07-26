#pragma once
#include "./BaseWindow.hpp"

template<class DERIVED_CLASS>
BaseWindow<DERIVED_CLASS>::BaseWindow(): 
    window_class_name(L"Window class"), 
    m_hwnd(NULL),
    pos_x(0),
    pos_y(0),
    width(0),
    height(0) {};

template<class DERIVED_CLASS>
BaseWindow<DERIVED_CLASS>::BaseWindow(const wchar_t* name, int x, int y, int width, int height): 
    window_class_name(L"Window class"),
    m_hwnd(NULL),
    window_name(window_name),
    pos_x(x),
    pos_y(y),
    width(width),
    height(height) {};

template <class DERIVED_CLASS>
LRESULT CALLBACK BaseWindow<DERIVED_CLASS>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    DERIVED_CLASS* pThis = NULL;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;

        pThis = (DERIVED_CLASS*)pCreate->lpCreateParams;

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hwnd = hwnd;
    }
    else {
        pThis = (DERIVED_CLASS*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (pThis) {
        return pThis->handleMessage(uMsg, wParam, lParam);
    }
    else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

template<class DERIVED_CLASS>
BOOL BaseWindow<DERIVED_CLASS>::create(DWORD dwStyle, DWORD dwExStyle, HWND hWndParent, HMENU hMenu) {
    WNDCLASS window_class = {};

    window_class.lpfnWndProc = DERIVED_CLASS::WindowProc;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.lpszClassName = className();

    RegisterClass(&window_class);

    m_hwnd = CreateWindowEx(
        dwExStyle,
        className(),
        window_name,
        dwStyle,
        pos_x,
        pos_y,
        width,
        height,
        hWndParent,
        hMenu,
        GetModuleHandle(NULL),
        this
    );

    return (m_hwnd ? TRUE : FALSE);
}

template<class DERIVED_CLASS>
HWND BaseWindow<DERIVED_CLASS>::getWindow() const {
    return m_hwnd; 
}