#include "wx/glcanvas.h"
#define GLM_ENABLE_EXPERIMENTAL

//glm for mathematical objects
// #include <glm/glm.hpp>                      
// #include <glm/gtc/matrix_transform.hpp>     
// #include <glm/gtc/quaternion.hpp>           
// #include <glm/gtx/quaternion.hpp>       
#include <iostream>

class MyApp : public wxApp{
    //virutal function for overriding and specific runtime properties 
    virtual bool OnInit();
};
class MyGLCanvas : public wxGLCanvas{
    public:
        MyGLCanvas(wxWindow *parent);
    private:
        //on action methods to ovverride
        void OnPaint(wxPaintEvent& event);
        
};

class MyGLContext : public wxGLContext{
    public: 
        MyGLContext(MyGLCanvas *canvas);
};

class MyFrame : public wxFrame{
    public: 
        MyFrame();
    private:
        MyGLCanvas *canvas;
        MyGLContext *context;
};

class pbox{
    public:

    private:
    
};

class physicsEngine{
    public:
        physicsEngine( ){

        };
    private:

};