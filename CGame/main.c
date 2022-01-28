#include <stdio.h>

#include "Window/Win32Window.h"
#include "Renderer/RendererContext.h"

int main()
{
    Win32Window *pWindow = (Win32Window *)malloc(sizeof(Win32Window));
    Win32Window_Init(pWindow, "Problem?", 1280, 720);
    Win32Window_CreateGLContext(pWindow);
    
    Renderer_Init(pWindow);
    
    while(1)
    {
        Renderer_Begin();
        Renderer_End();
        Win32Window_Poll(pWindow);
        Win32Window_SwapBuffers(pWindow);
    }
    
    return 1;
}