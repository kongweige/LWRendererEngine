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

  //���ڿ���������˳��
  bool startUp();
  void shutDown();

  //���������߼�����Ӧ�ó���ѭ��
  void run();

  //ÿ����ϵͳ��ʵ��
  DisplayManager gDisplayManager;
  InputManager gInputManager;
  SceneManager gSceneManager;
  //RenderManager gRenderManager;

};

#endif