#pragma once

#include <windows.h>

template<class DERIVED_CLASS>
class BaseWindow {
    protected: 
        HWND m_hwnd;
        const wchar_t* window_class_name;

    public:
        const wchar_t* window_name;
        int pos_x;
        int pos_y;
        int width;
        int height;
    
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        BaseWindow();
        BaseWindow(const wchar_t*, int, int, int, int);

        BOOL create(DWORD, DWORD dwExStyle = 0, HWND hWndParent = 0, HMENU hMenu = 0);

        HWND getWindow() const;
    
    protected: 
        virtual PCWSTR className() const = 0;
        virtual LRESULT handleMessage(UINT, WPARAM, LPARAM) = 0;
};

#include "BaseWindow_impl.hpp"