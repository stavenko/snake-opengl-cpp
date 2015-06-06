#pragma once
#include "segment.hpp"

using namespace std;
class Snake{
    public:
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
        
};
