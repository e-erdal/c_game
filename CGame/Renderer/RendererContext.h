/* date = January 28th 2022 5:32 pm */

#ifndef _RENDERER_CONTEXT_H
#define _RENDERER_CONTEXT_H

#include "Window/Win32Window.h"

typedef struct _RendererContext
{
    
} RendererContext;

void Renderer_Init(Win32Window *pWindow);
void Renderer_Begin();
void Renderer_End();

#endif //_RENDERER_CONTEXT_H
