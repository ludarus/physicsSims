#pragma once
#include "wx/glcanvas.h"
#include "MyGLCanvas.h"
class MyGLContext : public wxGLContext{
    public:
        MyGLContext(MyGLCanvas *canvas) : wxGLContext(canvas)
        {
            SetCurrent(*canvas);
            // rendering settings:

            // glMatrixMode(GL_PROJECTION);
        };
};