#pragma once
#include "snake.hpp"
#include <common/renderer.h>
#include <common/scene.h>
#include <common/perspectiveCamera.h>

class Game{
    private:
        Renderer renderer;
        Scene scene;
        PerspectiveCamera camera;
    private:
        Snake currentSnake;
        int moveSpeed = 1;
        int fieldWidth  = 50;
        int fieldHeight = 50;
    private:
        void _moveSnakeForSure(){
            if(currentSnake.segments.size() == 0){return;}
            std::cout << "MOVE" << std::endl;
            for(auto iter = currentSnake.segments.begin(); iter != currentSnake.segments.end(); iter++){
                std::cout << "loop" << std::endl;;
               (*iter) -> propagate(fieldWidth, fieldHeight ); 
            }
            std::cout << "MOVE2" << std::endl;

            for(auto iter = currentSnake.segments.rbegin(); iter != currentSnake.segments.rend()-1; iter++){
                auto next = iter + 1;
                (*iter)->setDirection((*next)->getDirection() );
            }
            std::cout << "END" << std::endl;
            
        }
        void moveSnake(float timeDiff){
            static float timeSumm = 0;
            timeSumm += timeDiff;
            if(timeSumm > moveSpeed) {
                _moveSnakeForSure();
                timeSumm = 0;
            };
        };
        void turn( vec2 dir ){
        };
        void renderSnake(){
            // move it's coords and call Renderer::render() method;
            renderer.render(scene, &camera);
        }
        void start(){
            currentSnake = Snake(4);
           
            scene.clear();
           std::cout << "put to scene: "<< currentSnake.segments.size() << std::endl;
           for(auto iter = currentSnake.segments.begin(); iter != currentSnake.segments.end(); iter++){
               std :: cout << "put to scene" << std :: endl;
               scene.add((*iter)->getBox());
           }
        };

        void getControls(){
            //if (glfwGetKey(renderer.getWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS){
                //start();
            //}
        }


    public:
        void setKeyBind(GLFWkeyfun fun){
            renderer.setKeyBind(fun);
        }
        void s(){
            start(); 
        }
        Game(){
            camera =  PerspectiveCamera(45, 4.0f/3.0f, 0.1f, 1000.0f);
            camera.lookAt(glm::vec3(0,10,100), glm::vec3(0,0,0), glm::vec3(0,1,0));
        }

        void init(){
           
            // bind events;
        }
        bool shouldClose(){
            return renderer.shouldClose();
        }
        void update(float timeDiff){
            getControls();
            moveSnake( timeDiff );
            renderSnake();
        }

};
