#pragma once
#include <glm/glm.hpp>
#include <common/box.h>
using namespace glm;
class Segment{
    private:
        vec2 position;
        vec2 direction;
        BoxObject box ;
    public:
        Segment(vec2 pos, vec2 dir){
            position =pos;
            direction = dir;

        }
        void setDirection(vec2 dir){
            direction = dir;
        };
        vec2 getDirection(){
            return direction;
        }
        void propagate(int maxX, int maxY){
            position += direction;
            position.x = int(position.x) % maxX;
            position.y = int(position.y) % maxY;
            box.setPosition(position.x, position.y, 0);
        }

        BoxObject *getBox(){
            return &box;
        }

};
