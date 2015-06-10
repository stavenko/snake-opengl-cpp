#pragma once
#include <common/object3d.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class BoxObject: public Object3D{
    private:
        std::vector<GeometryGroup> geometryGroups;
        glm::vec3 position = vec3(0,0,0);

    public:
        BoxObject(){
            static char* cvShader = "#version 400 core \n\
                layout(location=0) in vec3 position;\n \
                uniform mat4 projectionMatrix;\n \
                uniform mat4 viewMatrix;\n \
                uniform mat4 modelMatrix;\n \
                void main(){\n \
                    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0); \n \
                } \n";
            static char* cfShader = "#version 400 core\n\
                                     out vec4 color;\n\
                void main(){\n \
                     color = vec4(1, 0, 0, 0.0);\n \
                } \n";
            std::string vShader = std::string(cvShader);
            std::string fShader = std::string(cfShader);

            static const int vxLen = 36 * 3;
            static const GLfloat g_vertex_buffer_data[] = {
                -1.0f,-1.0f,-1.0f, // triangle 1 : begin
                -1.0f,-1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, // triangle 1 : end
                1.0f, 1.0f,-1.0f, // triangle 2 : begin
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f, // triangle 2 : end
                1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                1.0f,-1.0f,-1.0f,
                1.0f, 1.0f,-1.0f,
                1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                1.0f,-1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f,-1.0f,-1.0f,
                1.0f, 1.0f,-1.0f,
                1.0f,-1.0f,-1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f,-1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f,-1.0f, 1.0f
            }; 
            std::vector<float> vertexArray = std::vector<float>();
            vertexArray.assign(g_vertex_buffer_data, g_vertex_buffer_data + vxLen);
            std::cout << "Assign points" << std :: endl;

            geometryGroups = vector<GeometryGroup>();
            std::cout << "Create geometry group" << std :: endl;
            geometryGroups.push_back(GeometryGroup( vertexArray, vShader, fShader));
        }
        virtual ~BoxObject(){
            std::cout << "delete empty object" << std::endl;
        }

        virtual glm::mat4 getModelMatrix(){
            return glm::translate( mat4(1.0), position);
        };
        void setPosition(glm::vec3 v){
            position = v;
        }
        void setPosition(float x, float y, float z){
            position.x = x;
            position.y = y;
            position.z = z;
        }
        virtual std::vector<GeometryGroup> getGeometryGroups(){
            return geometryGroups;
        };
};
