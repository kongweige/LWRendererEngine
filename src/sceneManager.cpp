#include "controller/sceneManager.h"

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}

// 启动并加载默认场景，如果未加载成功会直接退出
bool SceneManager::startUp()
{
  currentSceneID = "Sponza";
  if (!loadScene(currentSceneID))
  {
    printf("Could not load default scene. No models succesfully loaded\n");
    return false;
  }
  return true;
}

void SceneManager::shutDown()
{
  delete currentScene;
}

//使用给定的ID加载场景。如果场景为空，将说明未成功在加载早期就退出
bool SceneManager::loadScene(std::string sceneID)
{
  currentScene = new Scene(sceneID);
  return !currentScene->loadingError;
}

void SceneManager::update(unsigned int deltaT)
{
  currentScene->update(deltaT);
}