#pragma once
#include "segment.hpp"

using namespace std;
using namespace glm;
class Snake{
    private :
        vector<Segment *> segments;
    public:

        Snake(){
            Snake(4);
        }
        Snake(int segmentAmount){
            segments = vector<Segment *>();
            int start = 10;
            for(int i =0; i< segmentAmount; i++){
                std::cout << "Creating segment:"<<i << std::endl;
                segments.push_back(new Segment(vec2(start-i, 25), vec2(1,0)));
            }
        }
        int length(){
            return segments.size();
        }
        Segment * head(){
            return segments.front();
        }
        void propagate(int fieldWidth, int fieldHeight){
            if(segments.size() == 0){return;}
            for(auto iter = segments.begin(); iter != segments.end(); iter++){
               (*iter) -> propagate(fieldWidth, fieldHeight ); 
            }
        }
        void copyDirections(){
            if(segments.size() == 0){return;}
            for(auto iter = segments.rbegin(); iter != segments.rend()-1; iter++){
                auto next = iter + 1;
                (*iter)->setDirection((*next)->getDirection() );
            }
        }
        bool isSelfEated(){
            Segment *s = segments.front();
            bool eated = false;
            for(auto iter = segments.begin() +1; iter != segments.end(); iter ++){
                if(glm::length(s->getPosition() - (*iter)->getPosition() ) < 0.99){
                    eated = true;
                }
            }
            return eated;
        }
        std::vector<Object3D *>  addSegments(int amount){
            Segment *s = segments.back();
            std::vector<Object3D *> addedSegments;
            vec2 dir = s->getDirection();
            vec2 pos = s->getPosition();
            for (int i =0; i< amount; i++){
                vec2 d = -dir*float(i+1);
                Segment *s = new Segment( pos+d, vec2(dir) );
                segments.push_back(s);
                addedSegments.push_back(s->getBox());
            }
            return addedSegments;
        }
        
};
