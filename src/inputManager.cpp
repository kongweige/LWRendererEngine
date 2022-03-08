#include "controller/inputManager.h"
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

//处理键盘鼠标输入
void InputManager::processInput(GLFWwindow* window)
{
  ImGuiIO& io = ImGui::GetIO();
  //检测imgui是否要使用鼠标
  if (io.WantCaptureKeyboard || io.WantCaptureMouse) 
  {
    //检测到与GUI交互暂停所有相机移动

  }
  //处理其他鼠标键盘任务
  else
  {
    handleEvent(window);
  }
}


void InputManager::handleEvent(GLFWwindow* window)
{
  bool isDown = glfwGetKeyScancode(GLFW_PRESS);
  bool wasDown = glfwGetKey(window, GLFW_RELEASE);
  std::cout << "------------" << std::endl;
  std::cout << isDown << std::endl;
  std::cout << wasDown << std::endl;
  std::cout << "------------" << std::endl;

  //这段代码需要优化 好瓦
  if (isDown || wasDown)
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
      return;
    }
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
      if (isDown)
      {
        sceneCamera->resetCamera();
      }
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('w');
        std::cout << "is down" << std::endl;
      if (wasDown)
        sceneCamera->activeMoveStates.erase('w');
        std::cout << "was down" << std::endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('s');
      if (wasDown)
        sceneCamera->activeMoveStates.erase('s');
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('a');
      if (wasDown)
        sceneCamera->activeMoveStates.erase('a');
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('d');
      if (wasDown)
        sceneCamera->activeMoveStates.erase('d');
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('q');
      if (wasDown)
        sceneCamera->activeMoveStates.erase('q');
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
      if (isDown)
        sceneCamera->activeMoveStates.insert('e');
      if (wasDown)
        sceneCamera->activeMoveStates.erase('e');
    }
  }
  //else if()


}