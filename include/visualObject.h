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
        //angle
        double θ;
        
        std::array<glm::dvec2, 4> points;

        double hyp;


    public: 
        
        double getHyp(){
            return hyp;
        }
        
        //only call this function inside of a glBegin block
        // this was very painful to make
        void drawLines(int w, int h)
        {
            glm::dvec2 scale = glm::dvec2(w / 1920.0, h / 1080.0);

            double Δx1 = size.x * cos(θ);
            double Δy1 = size.x * sin(θ);

            double Δx2 = size.y * sin(θ);
            double Δy2 = size.y * cos(θ);

            points =
                {
                    // top right                                    //scaling 🤮
                    glm::dvec2(d.x + Δx1 + Δx2, d.y - Δy1 + Δy2) * scale,
                    // bottom right
                    glm::dvec2(d.x + Δx1 - Δx2, d.y - Δy1 - Δy2) * scale,
                    // bottom left
                    glm::dvec2(d.x - Δx1 - Δx2, d.y + Δy1 - Δy2) * scale,
                    // top  left
                    glm::dvec2(d.x - Δx1 + Δx2, d.y + Δy1 + Δy2) * scale};

            glColor4f(colour[0], colour[1], colour[2], colour[3]);

            glVertex2d(points[0].x, points[0].y);
            glVertex2d(points[1].x, points[1].y);

            glVertex2d(points[1].x, points[1].y);
            glVertex2d(points[2].x, points[2].y);

            glVertex2d(points[2].x, points[2].y);
            glVertex2d(points[3].x, points[3].y);

            glVertex2d(points[3].x, points[3].y);
            glVertex2d(points[0].x, points[0].y);
        }
        glm::dvec2 getSize(){
            return size;
        }

        glm::dvec2 getPos(){
            return d;
        }

        std::array<glm::dvec2, 4> getPoints(){
            return points;
        }
};
