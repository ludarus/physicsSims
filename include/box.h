#pragma once

#include <glm/glm.hpp>

#include "visualObject.h"
#include "force.h"
#include "wx/glcanvas.h"
#define GLM_ENABLE_EXPERIMENTAL


class box : public visualObject{
    public:
        //constructors
        box(glm::dvec2 pos, glm::dvec2 siz, double mass, double grav = -9.81, double angle = 0, glm::dvec2 vi = glm::dvec2(0,0), double av = 0, glm::fvec4 col = glm::fvec4(0.0f, 0.0f, 1.0f, 1.0f)){
            d = pos;
            size = siz;
            m = mass;
            v = vi;
            colour = col;
            θ = angle * (M_PI/180.0);
            w = av;
            g = glm::dvec2(0, grav * m);

            //moment of inertia formula (for a rectangle): 
            I = (1.0/12.0) * m * (pow(size.x * 2, 2) + pow(size.y * 2, 2));
            std::cout<<I<<std::endl;

            // forces.push_back( force(0, glm::dvec2(0, g * m)) );
            //hypotenuse
            hyp = sqrt((size.x * size.x) + (size.y * size.y));
            //adding force 
            Fnet = glm::dvec2(0,0);
            // torques.push_back(200);
        }


        //overriding draw function for rotation
        

        void transform(glm::dvec2 transformation){
            d += transformation;
        }

        void rotate(double angle){
            θ += angle;
        }

        glm::dvec2 getFnet(){
            return Fnet;
        }

        void applyForce(force f){
            forces.push_back(f);
        }

        void setV0(){
            v = glm::dvec2(0,0);
        }

        void updateMovement(long dt){
            forces.push_back( force(0, g ));
            //calculating accelearation
            Fnet = glm::dvec2(0,0);
            //calculating net force
            for (force f : forces){
                Fnet += f.F;
            }
            //f = ma; a = f/m
            glm::dvec2 a = Fnet / m;
            // std::cout<<a.y<<std::endl;
            forces.clear();
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

        glm::dvec2 Fnet;

        //velocity
        glm::dvec2 v;

        //angular veloicty
        double w;

        //moment of inertia
        double I;

        //mass
        double m;

        //gravity force
        glm::dvec2 g;

};

