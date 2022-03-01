#include "controller/engine.h"
#include "imgui/imgui.h"

#include <stdio.h>

Engine::Engine(){}
Engine::~Engine() {}

void renderUI();

bool Engine::startUp()
{
  // Initial time
  unsigned int start = glfwGetTime();

  // initial all glfw and opengl related
  if (!gDisplayManager.startUp())
  {
    printf("Failed to initialize window display manager.\n");
    return false;
  }
  
  // initial scene manger and loads default scene
  if (!gSceneManager.startUp())
  {
    printf("Failed to initialize scene manager.\n");
    return false;
  }

  // Time spent in the whole loading process
  unsigned int deltaT = glfwGetTime() - start;
  printf("(Load time: %ums)\n", deltaT);
  return true;
}

void Engine::shutDown()
{
  gDisplayManager.shutDown();
  printf("Closed display manager.\n");
}

void Engine::run()
{
  GLFWwindow* window = gDisplayManager.getGlfwWindow();

  while (!glfwWindowShouldClose(window))
  {
    gDisplayManager.bind();

    renderUI();

    gDisplayManager.swapDisplayBuffer();
  }
  printf("run\n");
}

void renderUI() 
{
  bool bShowDemoWindow = true;
  // 显示ImGui自带的demo window
  ImGui::ShowDemoWindow(&bShowDemoWindow);
}