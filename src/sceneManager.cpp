#include "controller/sceneManager.h"

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}

// ����������Ĭ�ϳ�������������κ�ԭ��û�м��سɹ���ֱ���˳�
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

//ʹ�ø�����ID���س������������Ϊ�գ���˵��δ�ɹ��ڼ������ھ��˳�
bool SceneManager::loadScene(std::string sceneID)
{
  currentScene = new Scene(sceneID);
  return currentScene->loadingError;
}