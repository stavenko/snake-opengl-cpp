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
        Renderer(){
            std::cout << "init context" << std::endl;
            this->init = Init();
            init.glfw(3,3);
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
        

        void render(Scene scene, Camera *camera){
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            const std::vector<shared_ptr<Object3D>> meshes = scene.getObjects();
            for( auto iter = meshes.begin(); iter != meshes.end(); iter++ ){
                renderObject(*iter, camera->getViewMatrix(), camera->getProjectionMatrix());
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        };
        bool shouldClose(){
            return glfwWindowShouldClose(window);
        };
        ~Renderer(){
            std::cout << "delete renderer" << std:: endl;
            glDeleteVertexArrays(1, &VertexArrayID);
            glfwDestroyWindow(window);
            glfwTerminate();
        };
    private:
        void renderGeometryGroup(GeometryGroup &gg, glm::mat4 projectionMatrix, glm::mat4 viewMatrix,  glm::mat4 modelMatrix ){
            std::cout <<"GG render!" << std::endl;
            std::cout <<"1." << std::endl;
            glUseProgram(gg.getProgramID());
            setMatrix(gg.getProgramID(), "viewMatrix", viewMatrix);
            std::cout <<"2." << std::endl;
            setMatrix(gg.getProgramID(), "projectionMatrix", projectionMatrix);
            std::cout <<"3." << std::endl;
            setMatrix(gg.getProgramID(), "modelMatrix", modelMatrix);
            std::cout <<"4." << std::endl;
            std::cout <<"5." << std::endl;
            glEnableVertexAttribArray(0);
            std::cout <<"6." << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, gg.getVertexBuffer());
            std::cout <<"7." << std::endl;
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
            std::cout <<"8." << std::endl;
            glDrawArrays(GL_TRIANGLES, 0, 36);
            std::cout <<"9." << std::endl;
            glDisableVertexAttribArray(0);
            std::cout <<"0." << std::endl;
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
            std::cout << "set matrix"; 
            std::cout << "1.";
            GLuint id = glGetUniformLocation(programID, uName.c_str());
            std::cout << "2.";
            glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
            std::cout << "3.";
        }
};
