#include "controller/scene.h"
#include "controller/fileManager.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

Scene::Scene(const std::string& sceneName)
{
  std::string folderPath = "../assets/scenes/";
  std::string fileExtension = ".json";
  sceneID = sceneName;

  printf("\nBeginning Scene load, checking scene description file:\n");
  if (!FLOAD::checkFileValidity(folderPath + sceneName + fileExtension))
  {
    printf("Cannot find scene descriptor file for %s \n", sceneID.c_str());
    loadingError = true;  //为什么这要反着来一下
  }
  else
  {
    //加载所有摄像头、模型和灯光，如果失败则返回false
    loadingError = !loadContent();
  }
}

Scene::~Scene()
{

}

//-----------------------------场景加载-----------------------------------

//加载配置文件
bool Scene::loadContent()
{
  //读取json文件
  std::string folderPath = "../assets/scenes/";
  std::string fileExtension = ".json";
  std::string sceneConfigFilePath = folderPath + sceneID + fileExtension;
  std::ifstream file(sceneConfigFilePath.c_str());
  json configJson;
  file >> configJson;

  //查看json文件是和否是当前场景的并且格式正确
  if (configJson["sceneID"] != sceneID && ((unsigned int)configJson["models"].size() != 0))
  {
    printf("Error! Config file: %s does not belong to current scene, check configuration.\n", sceneConfigFilePath.c_str());
    return false;
  }
  
  //加载相机
  printf("Loading camera...\n");
  loadCamera(configJson);

  //加载场景模型
  printf("Loading models...\n");
  loadSceneModels(configJson);

  //加载天空盒
  printf("Loading skybox...\n");
  loadSkyBox(configJson);

  //加载光源
  printf("Loading lights...\n");
  loadLights(configJson);

  //生成环境地图
  printf("Generating environment maps...\n");
  generateEnvironmentMaps();
}

void Scene::loadCamera(const json& sceneConfigJson)
{
  //json cameraSettings = sceneConfigJson["camera"];
  //float speed = (float)cameraSettings["speed"];
  //float sens = (float)cameraSettings["mouseSens"];
  //float fov = (float)cameraSettings["fov"];
  //float nearP = (float)cameraSettings["nearPlane"];
  //float farP = (float)cameraSettings["farPlane"];



}
void Scene::loadSceneModels(const json& sceneConfigJson)
{

}
void Scene::loadSkyBox(const json& sceneConfigJson)
{

}
void Scene::loadLights(const json& sceneConfigJson)
{

}
void Scene::generateEnvironmentMaps()
{

}
