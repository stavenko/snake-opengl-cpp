#pragma once
#include <string>
#include <common/Init.h>
#include <common/scene.h>
#include <common/perspectiveCamera.h>
using std::string;

class Renderer{
    private:
        Init init;
        GLFWwindow *window;

    public:
        Renderer(){
            std::cout << "init context" << std::endl;
            this->init = Init();
            init.glfw(4,1);
            this->window = init.window();
            init.printWindowInfo(window);
            glfwMakeContextCurrent(window);
            init.glew();
            glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        };
        

        void render(Scene scene, Camera camera){
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            const std::vector<shared_ptr<Object3D>> meshes = scene.getObjects();
            for( auto iter = meshes.begin(); iter != meshes.end(); iter++ ){
                shared_ptr<Object3D> obj = *iter;
                renderObject(*obj, camera.getViewMatrix(), camera.getProjectionMatrix());
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        };
        bool shouldClose(){
            return glfwWindowShouldClose(window);
        };
        ~Renderer(){
          glfwDestroyWindow(window);
          glfwTerminate();
        };
    private:
        void renderGeometryGroup(GeometryGroup gg, glm::mat4 projectionMatrix, glm::mat4 viewMatrix,  glm::mat4 modelMatrix ){
            setMatrix(gg.getProgramID(), "viewMatrix", viewMatrix);
            setMatrix(gg.getProgramID(), "projectionMatrix", projectionMatrix);
            setMatrix(gg.getProgramID(), "modelMatrix", modelMatrix);
            glUseProgram(gg.getProgramID());
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, gg.getVertexBuffer());
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
        }
        void renderObject(Object3D obj, glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
            glm::mat4 modelMatrix = obj.getModelMatrix();

            for(auto iter = obj.getGeometryGroups().begin(); iter != obj.getGeometryGroups().end(); iter++){
                GeometryGroup gg = *iter;
                renderGeometryGroup(gg, projectionMatrix, viewMatrix, modelMatrix);
            }
            
        }

        void setMatrix(GLuint programID, string uName, glm::mat4 &matrix){
            GLuint id = glGetUniformLocation(programID, uName.c_str());
            glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
        }
};
