//wxwidgets and opengl
#include "wx/glcanvas.h"
#define GLM_ENABLE_EXPERIMENTAL

//glm for mathematical objects
#include <glm/glm.hpp>                      
#include <glm/gtc/matrix_transform.hpp>     
#include <glm/gtc/quaternion.hpp>           
#include <glm/gtx/quaternion.hpp>       

//c headers
#include <memory>
#include <iostream>

//other header files
#include "visualObject.h"
#include "force.h"
#include "box.h"
#include "physicsEngine.h"


//wxwidgets stuff
class MyApp : public wxApp{
    //virutal function for overriding and specific runtime properties 
    virtual bool OnInit();
};

class MyGLCanvas : public wxGLCanvas{
    public:
        MyGLCanvas(wxWindow *parent);
    private:
        wxTimer* refreshTimer;
        wxStopWatch* timeElapsed;
        physicsEngine* engine;

        wxLongLong previousTime = 0l;
        long dt;

        //on action methods to ovverride
        void OnPaint(wxPaintEvent &WXUNUSED(event))
        {
            // weird macro thing idk
            wxPaintDC dc(this);

            // getting window size
            int w, h;
            GetClientSize(&w, &h);
            glViewport(0, 0, w, h);

            // reconfiguring projection on resize
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, w, 0, h, -1, 1);

            // setting to model view for 2d
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // clearing frames with white colour
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // drawing
            glBegin(GL_LINES);
            // draw physics engine
            engine->refresh(w, h);
            glEnd();

            SwapBuffers();
        };

        //does physics no matter what
        void OnRefresh(wxTimerEvent& event){
        //     dt = (timeElapsed->TimeInMicro() - previousTime).GetValue();
        //     std::cout<<dt/1000.0<<std::endl;
        //     engine->compute(dt);
        //     previousTime = timeElapsed->TimeInMicro();
        };

        //updates screen on idle
        void OnIdle(wxIdleEvent& event){
            dt = (timeElapsed->TimeInMicro() - previousTime).GetValue();
            engine->compute(dt);
            Refresh(false);
            previousTime = timeElapsed->TimeInMicro();
            event.RequestMore();
        }
        
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