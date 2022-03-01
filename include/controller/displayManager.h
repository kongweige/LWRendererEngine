#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <GLFW/glfw3.h>

class DisplayManager
{
public:
  // The screen size is fixed and set at compile time 
  const static int SCREEN_WIDTH = 640;//1280; //640 1920
  const static int SCREEN_HEIGHT = 480;//720 ; //480 1080
  
  // Shader version used in ImGUI 
  const char* glsl_version = "#version 330";

  DisplayManager();
  ~DisplayManager();

  bool startUp();
  void shutDown();

  // Presenting the final rendered image to the display
  void bind();
  void swapDisplayBuffer();

  GLFWwindow* getGlfwWindow();

private:
  // Startup sub-function
  bool startGLFW();
  bool startOpenGL();
  bool createWindow();
  bool createGLContext();
  bool createImGuiContext();

  // glfw的上下文
  GLFWwindow* window;
};
#endif // DISPLAY_MANAGER_H
