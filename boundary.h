#include <glm/glm.hpp>

#include "visualObject.h"

class boundary : public visualObject{
    public:
        boundary(glm::dvec2 pos, glm::dvec2 siz, glm::fvec4 col = glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f)){
            d = pos;
            size = siz;
            colour = col;
        }

        glm::dvec2 getBottomLeft(){
            return d - size;
        }

        glm::dvec2 getTopRight(){
            return d + size;
        }
};