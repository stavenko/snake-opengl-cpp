#pragma once
#include <vector>
#include <glm/glm.hpp>

#ifdef __APPLE_CC__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include <common/geometryGroup.h>

class Object3D{
    public:
        virtual ~Object3D()=0;
        virtual glm::mat4 getModelMatrix()=0;
        virtual std::vector<GeometryGroup> getGeometryGroups() = 0;

};
Object3D::~Object3D(){
    //empty destructor
}
