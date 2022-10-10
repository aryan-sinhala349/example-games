#include "Window.h"

#include <iostream>

#define WindowStyle WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU

static HINSTANCE g_HInstance;

static const char* g_WindowClassTitle = "Tic-Tac-Toe";
static int g_WindowCount = 0;

LRESULT CALLBACK WndProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window(int width, int height, const char* title)
{
	//Create Window Class
	if (!g_WindowCount)
	{
		g_HInstance = GetModuleHandle(nullptr);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = g_HInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = g_WindowClassTitle;
		wc.hIconSm = nullptr;

		::RegisterClassEx(&wc);
	}

	RECT clientRect;
	::SetRect(&clientRect, 0, 0, width, height);

	::AdjustWindowRect(&clientRect, WindowStyle, false);

	width = clientRect.right - clientRect.left;
	height = clientRect.bottom - clientRect.top;

	m_WindowHandle = ::CreateWindow(
		g_WindowClassTitle, 
		title, 
		WindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		width, height, 
		nullptr, nullptr, g_HInstance, &m_WindowParams);
	g_WindowCount++;

	ShowWindow(m_WindowHandle, SW_SHOW);
}

Window::~Window()
{
	::DestroyWindow(m_WindowHandle);
	g_WindowCount--;

	if (!g_WindowCount)
		::UnregisterClass(g_WindowClassTitle, g_HInstance);
}

void Window::PollEvents()
{
	MSG msg;

	while (::PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessageA(&msg);
	}
}

LRESULT WndProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		Window::WindowParams* params = (Window::WindowParams*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)params);
	}

	switch (msg)
	{
		case WM_CLOSE:
		{
			Window::WindowParams* params = (Window::WindowParams*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
			params->OnClose();
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			Window::WindowParams* params = (Window::WindowParams*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
			params->OnClick(x, y);

			return 0;
		}
	}

	return DefWindowProc(windowHandle, msg, wParam, lParam);
}
