#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Scene
{
public:
  //���������ݹ�����json�ļ���
  Scene(const std::string& sceneFolder);
  ~Scene();

public:
  //��������״̬
  bool loadingError;

private:


};