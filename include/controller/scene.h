#include <iostream>
#include "glm/glm.hpp"
#include "nlohmann/json.hpp"

#include "controller/camera.h"
#include "controller/model.h"

using json = nlohmann::json;

class Scene
{
public:
  //将场景数据构建到json文件中
  Scene(const std::string& sceneFolder);
  ~Scene();

  //场景加载状态
  bool loadingError;

  //用于初始Camera的构造函数
  Camera* mainCamera;

private:
  //场景加载和地图生成，但并未写到内存中
  bool loadContent();
  void loadCamera(const json& sceneConfigJson);
  void loadSceneModels(const json& sceneConfigJson);
  void loadSkyBox(const json& sceneConfigJson);
  void loadLights(const json& sceneConfigJson);
  void generateEnvironmentMaps();

private:
  std::string sceneID;

  //Contains the models that remain after frustrum culling which is TB done
  std::vector<Model*> visibleModels;
  std::vector<Model*> modelsInScene;


};