/* date = January 28th 2022 4:40 pm */

#ifndef _WIN32_WINDOW_H
#define _WIN32_WINDOW_H

#include <Windows.h>

typedef struct _Win32Window
{
    HWND m_Handle;
    HINSTANCE m_Instance;
    
    HDC m_DC;
    HGLRC m_GLContext;
    
    int m_Width;
    int m_Height;
    
} Win32Window;

void Win32Window_Init(Win32Window *pWindow, const char *pTitle, int width, int height);
void Win32Window_Poll(Win32Window *pWindow);
void Win32Window_SwapBuffers(Win32Window *pWindow);
void Win32Window_CreateGLContext(Win32Window *pWindow);

#endif //_WIN32_WINDOW_H
