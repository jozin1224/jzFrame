#pragma once

#include <Windows.h>
#include <functional>
#include <map>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#define JZ_MODERN
#ifdef JZFRAME_EXPORTS
#define JZFRAME_API __declspec(dllexport)
#else
#define JZFRAME_API __declspec(dllimport)
#endif

#ifdef JZ_MODERN
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
const bool modern = true;
#else
const bool modern = false;
#endif

#ifndef JZ_WINDOWSLOOP
#define JZ_WINDOWSLOOP MSG msg = {}; while (GetMessage(&msg, NULL, 0, 0) > 0) { TranslateMessage(&msg); DispatchMessage(&msg);}
#endif

extern "C" {
	JZFRAME_API void nothing();
	JZFRAME_API void nothingHdc(HDC hdc, int w, int h);
}



class JZFRAME_API JZwindow {
private:
	std::function<void(HDC, int, int)> on_paint;
protected:
	int nextButtonId = 1001;

	const wchar_t* CLASS_NAME;
	std::map<int, std::function<void()>> buttonCallbacks;
public:
	int size_x;
	int size_y;
	const wchar_t* title;
	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND hwnd;
	virtual HWND init(HINSTANCE hInstance, int sizeX, int sizeY, const wchar_t* t, const wchar_t* classname = L"Jz Windows", COLORREF color = RGB(255, 255, 255), std::function<void(HDC, int, int)> paint = nothingHdc);
	virtual LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	HWND add_button(const wchar_t* Text, int x, int y, std::function<void()> onClick = nothing, int sizeX = 100, int sizeY = 100);
	HWND add_label(const wchar_t* Text, int x, int y, int sizeX, int sizeY);
};