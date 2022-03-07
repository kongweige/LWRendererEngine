#ifndef MODEL_H
#define MODEL_H

#include "controller/texture.h"
#include"controller/mesh.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <string>
#include <unordered_map>
#include <vector>

struct TransformParameters
{
  TransformParameters() :scaling(glm::vec3(1.0f)) { };
  glm::vec3 translation;
  float angle;
  glm::vec3 rotationAxis;
  glm::vec3 scaling;
};

struct Model
{
  Model(const std::string meshPath, const TransformParameters initParameters, bool IBL) : IBL(IBL)
  {
    loadModel(meshPath);
    modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, initParameters.translation);
    modelMatrix = glm::rotate(modelMatrix, initParameters.angle, initParameters.rotationAxis);
    modelMatrix = glm::scale(modelMatrix, initParameters.scaling);
  }

  void loadModel(std::string path);
  
  //模型处理和加载功能
  void processNode(aiNode* node, const aiScene* scene);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<unsigned int> processTextures(const aiMaterial* material);

  //MVP中的 model，将局部坐标变换到世界坐标
  bool IBL;
  glm::mat4 modelMatrix;
  std::vector<Mesh> meshes;

  //纹理优化，避免纹理重复加载
  std::unordered_map<std::string, Texture>textureAtlas;
  std::string directory, fileExtension;
};

#endif // !MODEL_H
