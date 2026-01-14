#pragma once

#include <glm/glm.hpp>

#include "visualObject.h"

class boundary : public visualObject{
    public:
        boundary(glm::dvec2 pos, glm::dvec2 siz, double angle = 0, glm::fvec4 col = glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f)){
            d = pos;
            size = siz;
            colour = col;
            θ = angle * (M_PI/180.0);
            hyp = sqrt((size.x * size.x) + (size.y * size.y));
        }

};