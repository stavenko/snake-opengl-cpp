#pragma once
#include "snake.hpp"
#include <common/renderer.h>
#include <common/scene.h>
#include <common/perspectiveCamera.h>
#include <stdlib.h>

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
        vec2 apple;
        BoxObject *appleBox;
    private:
        void eatApple(){
            std::cout << "eat apple"<< std::endl ;
            apple = vec2(rand()%fieldWidth, rand() % fieldHeight);
            appleBox -> setPosition(glm::vec3(apple, 0.0));
            currentSnake.addSegments(4);
            refreshScene();
        }
        void _moveSnakeForSure(){
            if(currentSnake.segments.size() == 0){return;}
            for(auto iter = currentSnake.segments.begin(); iter != currentSnake.segments.end(); iter++){
               (*iter) -> propagate(fieldWidth, fieldHeight ); 
            }
            if( glm::length (currentSnake.segments.front()->getPosition() - apple) < 0.99){
                eatApple();
            }

            for(auto iter = currentSnake.segments.rbegin(); iter != currentSnake.segments.rend()-1; iter++){
                auto next = iter + 1;
                (*iter)->setDirection((*next)->getDirection() );
            }
            
        }
        void moveSnake(float timeDiff){
            static float timeSumm = 0;
            timeSumm += timeDiff;
            if(timeSumm > moveSpeed) {
                _moveSnakeForSure();
                timeSumm = 0;
            };
        };
        void turn_left(){
            // lookup snake's head
            std::cout << "turn left" << std::endl;
            Segment *s = currentSnake.segments.front();
            vec2 dir = s->getDirection();
            vec2 ndir;
            if(dir.x != 0){
                if(dir.x < 0){ // south
                    ndir = vec2(0, -1);
                }else{
                    ndir = vec2(0, 1);
                }
            }else{
                if(dir.y<0){ // east
                    ndir = vec2(1,0);
                }else{
                    ndir = vec2( -1, 0);
                }
            }
            s->setDirection(ndir);
        }
        void turn_right(){
            // lookup snake's head
            std::cout << "turn right" << std::endl;
            Segment *s = currentSnake.segments.front();
            vec2 dir = s->getDirection();
            vec2 ndir;
            if(dir.x != 0){
                if(dir.x < 0){ // south
                    ndir = vec2(0, 1);
                }else{
                    ndir = vec2(0, -1);
                }
            }else{
                if(dir.y<0){ // east
                    ndir = vec2(-1,0);
                }else{
                    ndir = vec2( 1, 0);
                }
            }
            s->setDirection(ndir);
        }
        void turn( vec2 &dir ){

        };
        void renderSnake(){
            // move it's coords and call Renderer::render() method;
            renderer.render(scene, &camera);
        }
        void putApple(){
            apple = vec2(rand()% fieldWidth, rand() % fieldHeight );
            appleBox->setPosition(glm::vec3(apple, 0.0));
            scene.add(appleBox);


        }
        void refreshScene(){
            scene.clear();
            for(auto iter = currentSnake.segments.begin(); iter != currentSnake.segments.end(); iter++){
                std :: cout << "put to scene" << std :: endl;
                scene.add((*iter)->getBox());
            }
            putApple();

        }
        void start(){
            currentSnake = Snake(4);
            refreshScene();
            
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
        void input(int key, int scancode, int action, int mods){
            if(action == GLFW_RELEASE || action == GLFW_REPEAT) return;
            if(key == GLFW_KEY_SPACE){
                start();
            }
            if(key == GLFW_KEY_LEFT){
                turn_left();
            }
            if(key == GLFW_KEY_RIGHT){
                turn_right();
            }
        }
        Game(){
            camera =  PerspectiveCamera(45, 4.0f/3.0f, 0.1f, 1000.0f);
            camera.lookAt(glm::vec3(0,10,100), glm::vec3(0,0,0), glm::vec3(0,1,0));
        }

        void init(){
           
            appleBox = new BoxObject();
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
