#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
#include <set>

struct Camera
{
  Camera(glm::vec3 tar, glm::vec3 pos, float fov,
    float speed, float sens, float nearP, float farP)
  {

  }

  //ͨ������ı�����ľ���
  void resetCamera();

  //�洢��갴���¼�
  std::set<char> activeMoveStates;

};

#endif // !CAMERA_H
