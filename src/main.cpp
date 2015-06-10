// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#ifdef __APPLE_CC__
#include <OpenGL/gl3.h>
#define GLFW_INCLUDE_GLCOREARB
#else 
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <iostream>

#include "game_object.hpp"

using namespace glm;

static Game *globalGame;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    globalGame->input(key, scancode, action, mods);
}

int main( void )
{
  
    Game game = Game();
    game.init();
    game.setKeyBind(key_callback);

    globalGame = &game;
    //std::cout << "Renderer:" << std::endl;
    //Renderer renderer = Renderer();
    //std::cout << "Scene:" << std::endl;
    //Scene scene = Scene();
    //std::cout << "BoxObject:" << std::endl;
    //BoxObject bo = BoxObject();

    //std::cout << "add Box:" << std::endl;
    //scene.add(&bo);
    //std::cout << "create camera:" << std::endl;
    //PerspectiveCamera camera = PerspectiveCamera(45.f, 4.0f/3.0f, 0.1f, 10000.0f);
    //std::cout << "setup camera:" << std::endl;
    //camera.lookAt(glm::vec3(5, 50, 5), glm::vec3(0,0,0), glm::vec3(0,1,0));
    //std::cout << "it's actually done:" << std::endl;
    

  do{
      game.update(0.10);

  } // Check if the ESC key was pressed or the window was closed
  while( !game.shouldClose());

  // Close OpenGL window and terminate GLFW
  exit(EXIT_SUCCESS);
}
