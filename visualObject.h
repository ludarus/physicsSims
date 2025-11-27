#pragma once

#include <glm/glm.hpp>

//wxwidgets and opengl
#include "wx/glcanvas.h"
#define GLM_ENABLE_EXPERIMENTAL

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
        glm::dvec2 getSize(){
            return size;
        }

        glm::dvec2 getPos(){
            return d;
        }

        std::array<glm::dvec2, 4> getBounds(){
            return {glm::dvec2(d + size), glm::dvec2(d.x + size.x, d.y - size.y), glm::dvec2(d - size), glm::dvec2(d.x - size.x, d.y + size.y) };
        }
};
