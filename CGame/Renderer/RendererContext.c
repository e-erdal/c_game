#include "RendererContext.h"

#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

static RendererContext *pRendererCtx = NULL;

void Renderer_Init(Win32Window *pWindow)
{
    pRendererCtx = (RendererContext *)malloc(sizeof(RendererContext));
    
    int gladResult = gladLoadGL();
    
    if (!gladResult)
    {
        printf("Failed to initialize GLAD! Did you create GL context?");
        return;
    }
    
    printf("OpenGL init successful!\nOpenGL Version: %s\nGLSL Version: %s",
           glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    // Init viewport
    glViewport(0, 0, pWindow->m_Width, pWindow->m_Height);
}

void Renderer_Begin()
{
}

void Renderer_End()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}