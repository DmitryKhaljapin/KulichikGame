#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#include "./window/MainWindow/MainWindow.hpp"
#include "./Hero/Hero.hpp"
#include "./Map/Map.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    Map map;

    Hero hero(&map);

    MainWindow main_window(L"Kulichik Game", 0, 0, 1540, 825, &hero);

    if (!main_window.create(WS_OVERLAPPEDWINDOW)) return 0;

    ShowWindow(main_window.getWindow(), nCmdShow);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0 , 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

