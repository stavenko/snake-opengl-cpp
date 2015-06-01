#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <OpenGL/gl3.h>
#include <common/geometryGroup.h>

class Object3D{
    public:
        virtual ~Object3D(){};
        virtual glm::mat4 getModelMatrix() {};
        virtual std::vector<GeometryGroup> getGeometryGroups() {};

};
