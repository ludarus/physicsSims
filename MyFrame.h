#pragma once
#include "wx/glcanvas.h"
#include "MyGLCanvas.h"
#include "MyGLContext.h"
class MyFrame : public wxFrame{
    public: 
        MyFrame() : wxFrame(NULL, wxID_ANY, "physics sim - Luke Fadel", wxDefaultPosition, wxSize(1920, 1080)){
            canvas = new MyGLCanvas(this);
            context = new MyGLContext(canvas);
        };

    private:
        MyGLCanvas *canvas;
        MyGLContext *context;
};