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
  delete mainCamera;
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
  json cameraSettings = sceneConfigJson["camera"];
  float speed = (float)cameraSettings["speed"];
  float sens = (float)cameraSettings["mouseSens"];
  float fov = (float)cameraSettings["fov"];
  float nearP = (float)cameraSettings["nearPlane"];
  float farP = (float)cameraSettings["farPlane"];

  json position = cameraSettings["position"];
  glm::vec3 pos = glm::vec3((float)position[0], (float)position[1], (float)position[2]);

  json target = cameraSettings["target"];
  glm::vec3 tar = glm::vec3((float)target[0], (float)target[1], (float)target[2]);

  mainCamera = new Camera(tar, pos, farP, nearP, fov, sens, speed);
}

void Scene::loadSceneModels(const json& sceneConfigJson)
{
  //模型设置
  std::vector<std::string> modelMesh;
  std::string modelName;
  TransformParameters initParameters;
  bool IBL;
  unsigned int modelCount = (unsigned int)sceneConfigJson["models"].size();

  for (unsigned int i = 0; i < modelCount; ++i)
  {
    //获取模型 mesh 和 材质信息
    json currentModel = sceneConfigJson["models"][i];
    modelMesh.push_back(currentModel["mesh"]);
    IBL = currentModel["IBL"];

    modelName = modelMesh[i].substr(0, modelMesh[i].find_last_of('.'));

    //position
    json position = currentModel["position"];
    initParameters.translation = glm::vec3((float)position[0], (float)position[1], (float)position[2]);
    
    //rotation
    json rotation = currentModel["rotation"];
    initParameters.angle = glm::radians((float)rotation[0]);
    initParameters.rotationAxis = glm::vec3((float)rotation[1],
                                          (float)rotation[2],
                                          (float)rotation[3]);

    //scaling
    json scaling = currentModel["scaling"];
    initParameters.scaling = glm::vec3((float)scaling[0], (float)scaling[1], (float)scaling[2]);

    //尝试用已读取的初始化参数加载模型
    modelMesh[i] = "C:/github/LWRenderer/assets/models/" + modelName + "/" + modelMesh[i];
    if (!FLOAD::checkFileValidity(modelMesh[i])) 
    {
      printf("Error! Mesh: %s does not exist.\n", modelMesh[i].c_str());
    }
    else 
    {
      modelsInScene.push_back(new Model(modelMesh[i], initParameters, IBL));
    }
  }
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
