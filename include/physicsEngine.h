#include <glm/glm.hpp>
#include <memory>

#include "box.h"
#include "boundary.h"
#include "functions.h"

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
                    //basic test to see if in range to collide
                    if(dist(b.get()->getPos(), bo.get()->getPos()) < b.get()->getHyp() + bo.get()->getHyp()){
                        // std::cout<<"in range"<<std::endl;
                        //using sat to see if the things are colliding
                        if (SATcollide(b.get()->getPoints(), bo.get()->getPoints())){
                            //apply force in direction of boundary surface 
                            // std::cout<<b.get()->getFnet().y<<std::endl;
                            //getting fnet, and applying the opposite to the object
                            // b.get()->applyForce(force(1 , glm::dvec2(0, 1000)));

                            b.get()->applyForce(force(1, abs(b.get()->getFnet())));
                            b.get()->setV0();
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
