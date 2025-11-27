#pragma once

#include <glm/glm.hpp>

#include "visualObject.h"
#include "force.h"

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

            // std::cout<<a.x<<", "<<a.y<<std::endl;

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

