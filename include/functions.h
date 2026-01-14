#include <glm/glm.hpp>
#include <array>
#include <limits>
#include <glm/gtc/matrix_transform.hpp>     
#include <glm/gtc/quaternion.hpp>           
#include <glm/gtx/quaternion.hpp>     
double dist(glm::dvec2 a, glm::dvec2 b){
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double dot(glm::dvec2 a, glm::dvec2 b){
    return (a.x * b.x) + (a.y * b.y);
}

glm::dvec2 normalize(glm::dvec2 v){
    return v/glm::length(v);
}

//determines if two rotated rectangles are interesecting 
bool SATcollide(std::array<glm::dvec2, 4> a, std::array<glm::dvec2, 4> b){
    std::array<glm::dvec2, 4> axes = {
        //slope of each rect edge to get axes
        //also normalizing them for reasons
        //top-bottom for rect a
        normalize(glm::dvec2(a[0].x - a[3].x, a[0].y - a[3].y)),
        //left-right for rect a
        normalize(glm::dvec2(a[0].x - a[1].x, a[0].y - a[1].y)),
        //top-bottom for rect b
        normalize(glm::dvec2(b[0].x - b[3].x, b[0].y - b[3].y)),
        //left-right for rect a
        normalize(glm::dvec2(b[0].x - b[1].x, b[0].y - b[1].y))
    };

    bool notColliding = false;
    //iterating thru all the axes
    for (glm::dvec2 axis : axes){
        //projecting the corners of each rect onto axis
        glm::dvec2 intervalA = glm::dvec2(
            //first part of the interval is the min
            glm::min(
                dot(a[0], axis),
                dot(a[1], axis),
                dot(a[2], axis),
                dot(a[3], axis)
            ),
            //second part of the interval is the max
            glm::max(
                dot(a[0], axis),
                dot(a[1], axis),
                dot(a[2], axis),
                dot(a[3], axis)
            )
        );
        glm::dvec2 intervalB = glm::dvec2(
            //first part of the interval is the min
            glm::min(
                dot(b[0], axis),
                dot(b[1], axis),
                dot(b[2], axis),
                dot(b[3], axis)
            ),
            //second part of the interval is the max
            glm::max(
                dot(b[0], axis),
                dot(b[1], axis),
                dot(b[2], axis),
                dot(b[3], axis)
            )
        );

        //checking if intervals dont overlap
        if (( (intervalB.x < intervalA.x && intervalB.y < intervalA.x) || (intervalB.y > intervalA.y && intervalB.x > intervalA.y))){
            notColliding = true;
            // break;
            
        }
    }
    
    return !notColliding;

}