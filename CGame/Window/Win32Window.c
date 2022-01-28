#include "Win32Window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_PAINT:
        {
            //SwapBuffers(GetDC(hWnd));
            break;
        }
        default: break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Win32Window_Init(Win32Window *pWindow, const char *pTitle, int width, int height)
{
    static const DWORD kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
        | WS_VISIBLE | WS_POPUP | WS_MAXIMIZEBOX | WS_THICKFRAME;
    
    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));
    
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.hInstance = pWindow->m_Instance;
    wndClass.hIcon = LoadIconA(0, IDI_APPLICATION);
    wndClass.hCursor = LoadCursorA(0, IDC_ARROW);
    wndClass.lpszClassName = "C Game WND";
    
    RegisterClassExA(&wndClass);
    
    RECT rect = { 0, 0, (long)width, (long)height };
    AdjustWindowRectEx(&rect, kWindowStyle, 0, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
    
    pWindow->m_Handle = CreateWindowEx(0, wndClass.lpszClassName, pTitle, kWindowStyle,
                                       30, 30, rect.right - rect.left,
                                       rect.bottom - rect.top, 0, 0, 0, 0);
    
    ShowWindow(pWindow->m_Handle, SW_SHOW);
    UpdateWindow(pWindow->m_Handle);
    
    pWindow->m_Width = width;
    pWindow->m_Height = height;
}

void Win32Window_Poll(Win32Window *pWindow)
{
    MSG msg;
    
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window_SwapBuffers(Win32Window *pWindow)
{
    SwapBuffers(pWindow->m_DC);
}

void Win32Window_CreateGLContext(Win32Window *pWindow)
{
    HDC hdc = GetDC(pWindow->m_Handle);
    pWindow->m_DC = hdc;
    
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24; // RGB
    pfd.cDepthBits = 32; // Float
    pfd.cStencilBits = 8; // char
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
    
    pWindow->m_GLContext = wglCreateContext(hdc);
    wglMakeCurrent(hdc, pWindow->m_GLContext);
}