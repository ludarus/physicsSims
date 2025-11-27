#include <glm/glm.hpp>

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