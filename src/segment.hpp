#pragma once
#include <glm/glm.hpp>
#include <common/box.h>
using namespace glm;
class Segment{
    private:
        vec2 position;
        vec2 direction;
        BoxObject box ;

    private:
        float clamp(float v, float m, float M){
            if(v > M) return M;
            if(v < m) return m;
            return v;
        }
    public:
        Segment(vec2 pos, vec2 dir){
            position =pos;
            direction = dir;

        }
        void setDirection(vec2 dir){
            direction = dir;
        };
        const vec2 &getPosition(){
            return position;
        }
        const vec2 &getDirection(){
            return direction;
        }
        void propagate(int maxX, int maxY){
            position += direction;
            position.x = int(position.x) % maxX;
            position.y = int(position.y) % maxY;
            if(position.x < 0) {
                position.x += maxX;
            }
            if(position.y < 0){
                position.y += maxY;
            }
            box.setPosition(position.x, position.y, 0);
        }

        BoxObject *getBox(){
            return &box;
        }

};
