#include "wx/glcanvas.h"
#include <memory>
#define GLM_ENABLE_EXPERIMENTAL

//glm for mathematical objects
#include <glm/glm.hpp>                      
#include <glm/gtc/matrix_transform.hpp>     
#include <glm/gtc/quaternion.hpp>           
#include <glm/gtx/quaternion.hpp>       
#include <iostream>


struct force{
    glm::dvec2 F;
    int type;
    /*
    Force ids:
    0 = gravity
    1 = contact forces
    */

    public:
        //constructor
        force(int id, glm::dvec2 f = glm::dvec2(0, 0)){
            type = id;
            F = f;
        }
};


class visualObject{
    protected:
        //colour
        glm::fvec4 colour;

        //position
        glm::dvec2 d;

        //half extents
        glm::dvec2 size;

    public: 
        //only call this function inside of a glBegin block
        void drawLines(int w, int h){
            //setting colour
            glColor4f(colour[0], colour[1], colour[2], colour[3]);

            //scaling 
            glm::dvec2 sd = d * glm::dvec2(w/1920.0, h/1080.0);
            glm::dvec2 ss = size * glm::dvec2(w/1920.0, h/1080.0);

            //drawing with position as the center 
            glVertex2d(sd.x - ss.x, sd.y - ss.y);
            glVertex2d(sd.x - ss.x, sd.y + ss.y);

            glVertex2d(sd.x - ss.x, sd.y + ss.y);
            glVertex2d(sd.x + ss.x, sd.y + ss.y);

            glVertex2d(sd.x + ss.x, sd.y + ss.y);
            glVertex2d(sd.x + ss.x, sd.y - ss.y);

            glVertex2d(sd.x + ss.x, sd.y - ss.y);
            glVertex2d(sd.x - ss.x, sd.y - ss.y);
        }
};

//probably make this extend object or something 
//update: not very useful to make it a child
class box : public visualObject{
    public:
        //constructors
        box(glm::dvec2 pos, glm::dvec2 siz, double mass, double g, glm::dvec2 vi = glm::dvec2(0,0), glm::fvec4 col = glm::fvec4(0.0f, 0.0f, 1.0f, 1.0f)){
            d = pos;
            size = siz;
            m = mass;
            v = vi;
            colour = col;
            forces.push_back( force(0, glm::dvec2(0, g * m)) );
        }

        void transform(glm::dvec2 transformation){
            d += transformation;
        }

        void updateMovement(long dt){
            glm::dvec2 a = glm::dvec2(0,0);

            //calculating net force
            for (force f : forces){
                a += f.F;
            }

            //f = ma; a = f/m
            a /= m;

            std::cout<<a.x<<", "<<a.y<<std::endl;

            //changing velocity based on acceleration
            v += a * (dt/1000000.0);

            //changing distance based on veloicty 
            transform(glm::dvec2(v.x * (dt/1000000.0), v.y * (dt/1000000.0)));
        }

    private:
        //data members

        std::vector<force> forces;

        //velocity
        glm::dvec2 v;

        //mass
        double m;

};

class boundary : public visualObject{
    public:
        boundary(glm::dvec2 pos, glm::dvec2 siz, glm::fvec4 col = glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f)){
            d = pos;
            size = siz;
            colour = col;
        }
 };

class physicsEngine{
    public:
        physicsEngine(){

        };

        const double g = -9.81;

        void compute(long dt){
            //updating movement and forces
            for (std::shared_ptr<box> b : boxes){
                b.get()->updateMovement(dt);
            }
        }

        //call inside of glbegin
        void refresh(int w, int h){
            for (std::shared_ptr<boundary> bo : boundaries){
                bo.get()->drawLines(w, h);
            }
 
            for (std::shared_ptr<box> b : boxes){
                b.get()->drawLines(w, h);
            }
        }

        //use make_shared to create this
        void addBox(std::shared_ptr<box> b){
            boxes.push_back(b);
        }

        void addBoundary(std::shared_ptr<boundary> b){
            boundaries.push_back(b);
        }
    private:

        std::vector<std::shared_ptr<box>> boxes;
        std::vector<std::shared_ptr<boundary>> boundaries;

};

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