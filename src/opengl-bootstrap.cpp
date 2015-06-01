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

#include <common/object3d.h>
#include <common/geometryGroup.h>
#include <common/box.h>

#include <common/camera.h>
#include <common/perspectiveCamera.h>

#include <common/renderer.h>
#include <common/scene.h>

using namespace glm;


int main( void )
{
  
    std::cout << "Renderer:" << std::endl;
    Renderer renderer = Renderer();
    std::cout << "Scene:" << std::endl;
    Scene scene = Scene();
    std::cout << "BoxObject:" << std::endl;
    BoxObject bo = BoxObject();

    std::cout << "add Box:" << std::endl;
    scene.add(&bo);
    std::cout << "create camera:" << std::endl;
    PerspectiveCamera camera = PerspectiveCamera(45.f, 3.0f/4.0f, 1.0f, 10000.0f);
    std::cout << "setup camera:" << std::endl;
    camera.lookAt(glm::vec3(10, 50, 10), glm::vec3(0,0,0), glm::vec3(0,1,0));

  do{
      std::cout << "looping:" << std::endl;
      renderer.render(scene, camera);
      std::cout <<"llops"<<std::endl;

  } // Check if the ESC key was pressed or the window was closed
  while( !renderer.shouldClose());

  // Close OpenGL window and terminate GLFW
  exit(EXIT_SUCCESS);
}
