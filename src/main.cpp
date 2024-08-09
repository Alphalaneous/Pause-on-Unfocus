#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace geode::prelude;

LONG_PTR oWindowProc;
bool newWindowProcSet = false;

LRESULT CALLBACK nWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
	case WM_SIZE:
	case WM_MOVE:
    case WM_KILLFOCUS:
        if (PlayLayer* playLayer = PlayLayer::get()) {
            playLayer->pauseGame(true);
        }
        break;
    }

    return CallWindowProc((WNDPROC)oWindowProc, hwnd, msg, wparam, lparam);
}

HWND getWindowHandle() {
    return WindowFromDC(wglGetCurrentDC());
}

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		if (!newWindowProcSet) {
			oWindowProc = SetWindowLongPtrA(getWindowHandle(), -4, (LONG_PTR)nWindowProc);
    		newWindowProcSet = true;
		}

		return true;
	}
};