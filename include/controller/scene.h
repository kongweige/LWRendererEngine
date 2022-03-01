#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Scene
{
public:
  //将场景数据构建到json文件中
  Scene(const std::string& sceneFolder);
  ~Scene();

  //场景加载状态
  bool loadingError;

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


};