//luke fadel
// nov 24, 2025
//physics simulation 

//header files for libraries

#include <wx/wxprec.h>

#define GLM_ENABLE_EXPERIMENTAL

//defining macro and importing more libs 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
 
#include "main.h"
#include <iostream>

//glm for mathematical objects
// #include <glm/glm.hpp>      
// #include <glm/gtc/type_ptr.hpp>                
// #include <glm/gtc/matrix_transform.hpp>     
// #include <glm/gtc/quaternion.hpp>           
// #include <glm/gtx/quaternion.hpp>          



//enums
enum{
    DEEZ_NUTS = 69
};

//overriding app to make frame

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "physics sim - Luke Fadel"){
    canvas = new MyGLCanvas(this);
    context = new MyGLContext(canvas);
};

MyGLContext::MyGLContext(MyGLCanvas *canvas) : wxGLContext(canvas){
    SetCurrent(*canvas);
    //rendering settings:

    // glMatrixMode(GL_PROJECTION);
};

MyGLCanvas::MyGLCanvas(wxWindow *parent) : wxGLCanvas(parent,
        []{
            wxGLAttributes attrs;
            attrs.Defaults();
            attrs.PlatformDefaults(); 
            attrs.EndList();
            return attrs;
        }(),
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxFULL_REPAINT_ON_RESIZE){
    Bind(wxEVT_PAINT, &OnPaint, this);
};

void MyGLCanvas::OnPaint(wxPaintEvent & WXUNUSED(event)){
    //weird macro thing idk
    wxPaintDC dc (this);

    //getting window size
    int w, h;
    GetClientSize(&w, &h);
    glViewport(0, 0, w, h);

    //reconfiguring projection on resize
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);

    //setting to model view for 2d
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //clearing frames with white colour
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //setting "pen" colour
    glColor3f(1.0f, 0.0f, 0.0f);

    //drawing
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(w, h);
    glEnd();

    SwapBuffers();
};


//stupid macro
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    //making a new frame
    MyFrame * frame = new MyFrame();
    frame->Show(true);
    return true;
};
