#include "GLFW/glfw3.h"
#include "camera.h"

class InputManager
{
public:
  InputManager();
  ~InputManager();

  //处理键盘鼠标输入
  void processInput(GLFWwindow* window);

private:
  Camera* sceneCamera;

  //处理所有事件
  void handleEvent(GLFWwindow* window);
};