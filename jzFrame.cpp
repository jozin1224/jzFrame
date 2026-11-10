#include "jzFrame.hpp"


void nothingHdc(HDC hdc, int w, int h) {}
void nothing() {}
HWND JZwindow::init(HINSTANCE hInstance, int sizeX, int sizeY, const wchar_t* t, const wchar_t* classname, COLORREF color, std::function<void(HDC, int, int)> paint) {
	this->size_x = sizeX;
	this->size_y = sizeY;
	this->title = t;
	this->CLASS_NAME = classname;
	this->on_paint = paint;

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = JZwindow::StaticWindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = this->CLASS_NAME;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = CreateSolidBrush(color);
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(
		0,
		this->CLASS_NAME,
		this->title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		this->size_x, this->size_y,
		NULL, NULL, hInstance, this
	);

	if (hwnd != NULL) {
		ShowWindow(hwnd, SW_SHOW);
	}
	this->hwnd = hwnd;
	return hwnd;
}
LRESULT CALLBACK JZwindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	JZwindow* pThis = nullptr;

	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (JZwindow*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		pThis->hwnd = hwnd;
	}
	else {
		pThis = (JZwindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (pThis) {
		return pThis->handleMessage(uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
LRESULT JZwindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND: {
		int id = LOWORD(wParam);
		if (HIWORD(wParam) == BN_CLICKED && buttonCallbacks.count(id)) {
			buttonCallbacks[id]();
		}
		break;
	}
	case WM_CTLCOLORSTATIC: {
		HDC hdcStatic = (HDC)wParam;

		SetBkMode(hdcStatic, TRANSPARENT);

		return (INT_PTR)GetStockObject(NULL_BRUSH);
	}
	case WM_PAINT: {
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rect;
		int w;
		int h;
		hdc = BeginPaint(hwnd, &ps);
		if (GetClientRect(hwnd, &rect)) {
			int w = rect.right; 
			int h = rect.bottom; 
			if (this->on_paint) {
				this->on_paint(hdc, w, h);
			}
		}


		EndPaint(hwnd, &ps);
		return 0;
	}
	}
	return DefWindowProc(this->hwnd, uMsg, wParam, lParam);
}
HWND JZwindow::add_button(const wchar_t* Text, int x, int y, std::function<void()> onClick, int sizeX, int sizeY) {
	HWND dad = this->hwnd;
	int id = nextButtonId++;

	HWND hwndButton = CreateWindow(
		L"BUTTON",
		Text,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		x, y, sizeX, sizeY,
		dad,
		(HMENU)(INT_PTR)id,
		(HINSTANCE)GetWindowLongPtr(dad, GWLP_HINSTANCE),
		NULL
	);
	if (hwndButton && onClick) {
		buttonCallbacks[id] = onClick;
	}
	if (modern) {
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont, TRUE);
	}


	return hwndButton;
}
HWND JZwindow::add_label(const wchar_t* Text, int x, int y, int sizeX, int sizeY) {
	HWND hwndLabel = CreateWindow(
		L"STATIC",             
		Text,                   
		WS_VISIBLE | WS_CHILD,  
		x, y, sizeX, sizeY,
		this->hwnd,
		NULL,
		(HINSTANCE)GetWindowLongPtr(this->hwnd, GWLP_HINSTANCE),
		NULL
	);
	if (modern) {
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
	}
	return hwndLabel;


}


