#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "controller/scene.h"
#include <string>


class SceneManager
{
public:
  SceneManager();
  ~SceneManager();

  //初始化和关闭所有与场景相关的
  bool startUp();
  void shutDown();

  //更新当前场景
  void update(unsigned int deltaT);

private:
  bool loadScene(std::string sceneID);

  //String could probably be an enum instead, but it's easier this way to build
  //the relative paths if it is a string.
  std::string currentSceneID;
  Scene* currentScene;

};
#endif