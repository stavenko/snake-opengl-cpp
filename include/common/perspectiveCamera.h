#pragma once
#include <common/camera.h>
#include <glm/gtc/matrix_transform.hpp>
class PerspectiveCamera:public Camera{
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
    public:
        PerspectiveCamera(float fov, float aspect, float near, float far){
            this->projectionMatrix = glm::perspective( fov, aspect, near, far);
            this->viewMatrix = glm::mat4();
        };
        void lookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up){
            this->viewMatrix = glm::lookAt(eye, target, up);
        }
        virtual const glm::mat4 getViewMatrix(){
            return this->viewMatrix;
        }
        virtual const glm::mat4 getProjectionMatrix(){
            return this->projectionMatrix;
        }
};
