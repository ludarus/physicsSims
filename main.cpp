//luke fadel
// nov 24, 2025
//physics simulation 

//header files for libraries

//for timer stuff

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
    REFRESH_TIMER = wxID_HIGHEST + 1
};

//overriding app to make frame

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "physics sim - Luke Fadel", wxDefaultPosition, wxSize(1920, 1080)){
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
    
    engine = new physicsEngine();
    engine ->addBox(std::make_shared<box>(glm::dvec2(100, 1000), glm::dvec2(10, 10), 10, glm::dvec2(10, 10), glm::fvec4(0.5f, 1.0f, 0.0f, 1.0f)));
    
    engine->addBoundary(std::make_shared<boundary>(glm::dvec2(990, 10), glm::dvec2(990, 5)));
    refreshTimer = new wxTimer(this, REFRESH_TIMER);
    timeElapsed = new wxStopWatch();
    Bind(wxEVT_PAINT, &OnPaint, this);
    Bind(wxEVT_TIMER, &OnRefresh, this, REFRESH_TIMER);
    Bind(wxEVT_IDLE, &OnIdle, this);
    timeElapsed->Start();
    //60hz physics refresh
    // refreshTimer->Start(16, wxTIMER_CONTINUOUS);
};


//stupid macro
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    //making a new frame
    MyFrame * frame = new MyFrame();
    frame->Show(true);
    return true;
};
