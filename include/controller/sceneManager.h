#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "controller/scene.h"
#include <string>


class SceneManager
{
public:
  SceneManager();
  ~SceneManager();

  //Initializes and Closes all sence related stuff
  bool startUp();
  void shutDown();

private:
  bool loadScene(std::string sceneID);

  //String could probably be an enum instead, but it's easier this way to build
  //the relative paths if it is a string.
  std::string currentSceneID;
  Scene* currentScene;

};
#endif