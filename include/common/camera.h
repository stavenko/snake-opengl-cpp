#pragma once
#include <glm/glm.hpp>

class Camera{
    public:
        virtual const glm::mat4 getViewMatrix() {};
        virtual const glm::mat4 getProjectionMatrix() {};
        virtual void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up) {}; 
};
