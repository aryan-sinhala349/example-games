#include <iostream>

#include "Window.h"

static bool g_Running = true;

void* operator new(std::size_t size)
{
    std::cout << "Allocating " << size << " bytes" << std::endl;
    return std::malloc(size);
}

void operator delete(void* ptr, std::size_t size)
{
    std::cout << "Deallocating " << size << " bytes" << std::endl;
    return std::free(ptr);
}

void OnClose()
{
    g_Running = false;
}

void OnClick(int x, int y)
{
    std::cout << "Left click at (" << x << ", " << y << ")" << std::endl;
}

int main(int argc, char** argv)
{
    Window* window = new Window(360, 360, "Tic-Tac-Toe");

    window->SetCloseCallback(OnClose);
    window->SetClickCallback(OnClick);

    while (g_Running)
    {
        window->PollEvents();
    }

    delete window;

    system("pause");

    return 0;
}
