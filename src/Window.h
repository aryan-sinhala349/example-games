#pragma once

#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#include <Windows.h>

#include <functional>

class Window
{
public:
    struct WindowParams
    {
        using CloseCallback = std::function<void()>;
        using ClickCallback = std::function<void(int x, int y)>;

        CloseCallback OnClose;
        ClickCallback OnClick;
    };

    Window(int width, int height, const char* title);
    virtual ~Window();

    void PollEvents();

    void SetCloseCallback(WindowParams::CloseCallback callback) { m_WindowParams.OnClose = callback; }
    void SetClickCallback(WindowParams::ClickCallback callback) { m_WindowParams.OnClick = callback; }

private:
    HWND m_WindowHandle;
    WindowParams m_WindowParams;
};
