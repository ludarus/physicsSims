#pragma once
#include <wx/wx.h>
#include "wx/glcanvas.h"
#include "physicsEngine.h"
#include "enums.h"
#include <cmath>

class MyGLCanvas : public wxGLCanvas{
    public:
        //overriding
        MyGLCanvas(wxWindow *parent) : wxGLCanvas(parent,
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
            engine->addBox(std::make_shared<box>(glm::dvec2(100, 1000), glm::dvec2(10, 40), 10, engine->g,  M_PI, glm::dvec2(0, 0), 0, glm::fvec4(0.0f, 0.0f, 0.0f, 1.0f)));

            engine->addBoundary(std::make_shared<boundary>(glm::dvec2(965, 15), glm::dvec2(940, 5)));

            refreshTimer = new wxTimer(this, REFRESH_TIMER);
            timeElapsed = new wxStopWatch();
            Bind(wxEVT_PAINT, &OnPaint, this);
            Bind(wxEVT_TIMER, &OnRefresh, this, REFRESH_TIMER);
            Bind(wxEVT_IDLE, &OnIdle, this);
            timeElapsed->Start();
            // 60hz physics refresh
            //  refreshTimer->Start(16, wxTIMER_CONTINUOUS);
        };

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

