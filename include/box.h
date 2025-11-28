#pragma once

#include <glm/glm.hpp>

#include "visualObject.h"
#include "force.h"
#include "wx/glcanvas.h"
#define GLM_ENABLE_EXPERIMENTAL


class box : public visualObject{
    public:
        //constructors
        box(glm::dvec2 pos, glm::dvec2 siz, double mass, double g, double angle = 0, glm::dvec2 vi = glm::dvec2(0,0), double av = 0, glm::fvec4 col = glm::fvec4(0.0f, 0.0f, 1.0f, 1.0f)){
            d = pos;
            size = siz;
            m = mass;
            v = vi;
            colour = col;
            θ = angle;
            w = av;

            //moment of inertia formula (for a rectangle): 
            I = (1.0/12.0) * m * (pow(size.x * 2, 2) + pow(size.y * 2, 2));
            std::cout<<I<<std::endl;

            //internal angle to corner
            shapeInfo[1] = atan(size.y/size.x);
            //hypotenuse
            shapeInfo[0] = sqrt( pow(size.y, 2) + pow(size.x, 2) );
            
            // forces.push_back( force(0, glm::dvec2(0, g * m)) );
            torques.push_back(200);
        }


        //overriding draw function for rotation
        //this was very painful to make
        void drawLines(int w, int h){
            double Δx1 = size.x * cos(θ);
            double Δy1 = size.x * sin(θ);

            double Δx2 = size.y * sin(θ);
            double Δy2 = size.y * cos(θ);

            std::array<glm::dvec2, 4> points = 
            {
                //top right
                glm::dvec2( d.x + Δx1 + Δx2 , d.y - Δy1 + Δy2),
                //bottom right
                glm::dvec2( d.x + Δx1 - Δx2 , d.y - Δy1 - Δy2),
                //bottom left
                glm::dvec2( d.x - Δx1 - Δx2 , d.y + Δy1 - Δy2),
                //top  left
                glm::dvec2( d.x - Δx1 + Δx2 , d.y + Δy1 + Δy2)
            };

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

        void transform(glm::dvec2 transformation){
            d += transformation;
        }

        void rotate(double angle){
            θ += angle;
        }

        void updateMovement(long dt){
            //calculating accelearation
            glm::dvec2 a = glm::dvec2(0,0);

            //calculating net force
            for (force f : forces){
                a += f.F;
            }

            //f = ma; a = f/m
            a /= m;

            //calcualting angular acceleartaion
            double α = 0.0;

            //net torque
            for (double τ : torques){
                α += τ; 
            }

            // τ = Iα ; α = τ / I
            α /= I;

            //changing velocity based on acceleration
            //linear
            v += a * (dt/1000000.0);
            //angular
            w += α * (dt/1000000.0);
        
            //changing distance based on veloicty 
            transform(glm::dvec2(v.x * (dt/1000000.0), v.y * (dt/1000000.0)));

            //changle angle based on angular velocity
            rotate(w * (dt/1000000.0));
        }

    private:
        //data members
        std::vector<force> forces;

        std::vector<double> torques;

        //angle
        double θ;

        //velocity
        glm::dvec2 v;

        //angular veloicty
        double w;

        //moment of inertia
        double I;

        //mass
        double m;

        //for rotation:
        std::array<double, 2> shapeInfo;

};

