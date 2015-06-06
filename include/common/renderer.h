#pragma once
#include <string>
#include <memory>
#include <common/Init.h>
#include <common/scene.h>
#include <common/perspectiveCamera.h>
using std::string;

class Renderer{
    private:
        Init init;
        GLFWwindow *window;
        GLuint VertexArrayID;

    public:
        const GLFWwindow * getWindow(){
            return window;
        }                
        Renderer(){

            std::cout << "init context" << std::endl;
            this->init = Init();
#ifdef __APPLE_CC__
            init.glfw(3,2);
#else 
            init.glfw(3,3);
#endif

            this->window = init.window();
            init.printWindowInfo(window);
            glfwMakeContextCurrent(window);
            init.glew();
            glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

            std:: cout << "1.";
            glGenVertexArrays(1, &VertexArrayID);
            std:: cout << "2.";
           
            glBindVertexArray(VertexArrayID);
            std:: cout << "3." << VertexArrayID << std::endl;

        };
        

        void render(Scene &scene, Camera *camera){
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            const std::vector<shared_ptr<Object3D>> meshes = scene.getObjects();
            for( auto iter = meshes.begin(); iter != meshes.end(); iter++ ){
                std::cout << "Render#"<< std::endl;
                renderObject(*iter, camera->getViewMatrix(), camera->getProjectionMatrix());
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        };
        bool shouldClose(){
            return glfwWindowShouldClose(window);
        };
        void setKeyBind(GLFWkeyfun fun){
            glfwSetKeyCallback(window, fun);
        }
        ~Renderer(){
            std::cout << "delete renderer" << std:: endl;
            glDeleteVertexArrays(1, &VertexArrayID);
            glfwDestroyWindow(window);
            glfwTerminate();
        };
    private:
        void renderGeometryGroup(GeometryGroup &gg, glm::mat4 projectionMatrix, glm::mat4 viewMatrix,  glm::mat4 modelMatrix ){
            glUseProgram(gg.getProgramID());
            setMatrix(gg.getProgramID(), "viewMatrix", viewMatrix);
            setMatrix(gg.getProgramID(), "projectionMatrix", projectionMatrix);
            setMatrix(gg.getProgramID(), "modelMatrix", modelMatrix);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, gg.getVertexBuffer());
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDisableVertexAttribArray(0);
        }
        void renderObject(shared_ptr<Object3D> objPtr, glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
            glm::mat4 modelMatrix = objPtr->getModelMatrix();
            std::vector<GeometryGroup> groups = objPtr->getGeometryGroups();
            for(auto iter = groups.begin(); iter != groups.end(); iter++){
                GeometryGroup gg = *iter;
                renderGeometryGroup(gg, projectionMatrix, viewMatrix, modelMatrix);
            }
        }
        void setMatrix(GLuint programID, string uName, glm::mat4 &matrix){
            GLuint id = glGetUniformLocation(programID, uName.c_str());
            glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
        }
};
