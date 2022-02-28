#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Scene
{
public:
  //将场景数据构建到json文件中
  Scene(const std::string& sceneFolder);
  ~Scene();

public:
  //场景加载状态
  bool loadingError;

private:


};