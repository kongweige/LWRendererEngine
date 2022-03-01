#ifndef ENGINE_H
#define ENGINE_H

#include "controller/displayManager.h"
#include "controller/inputManager.h"
#include "controller/renderManager.h"
#include "controller/sceneManager.h"

struct Engine
{
  Engine();
  ~Engine();

  //用于控制启动的顺序
  bool startUp();
  void shutDown();

  //包含所有逻辑和主应用程序循环
  void run();

  //每个子系统的实例
  DisplayManager gDisplayManager;
  InputManager gInputManager;
  SceneManager gSceneManager;
  //RenderManager gRenderManager;

};

#endif