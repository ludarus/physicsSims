#include <glm/glm.hpp>
#include <memory>

#include "box.h"
#include "boundary.h"

class physicsEngine{
    public:
        physicsEngine(){

        };

        const double g = -9.81;

        void compute(long dt){
            
            //updating movement and forces
            for (std::shared_ptr<box> b : boxes){
                // collisions
                for (std::shared_ptr<boundary> bo : boundaries){
                    //iterate thru all the points (nessesary for rotationgal stuf)
                    for (glm::dvec2 point : b.get()->getBounds()){
                        //if one of the points are in bounds, then collide
                        if ((point.y > bo.get()->getBottomLeft().y && point.y < bo.get()->getTopRight().y) && ((point.x > bo.get()->getBottomLeft().x && point.x < bo.get()->getTopRight().x))){
                            //apply force 
                            std::cout<<"colliding"<<std::endl;
                            break;
                        }

                    }
                }
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
