#include "controller/model.h"
#include <string>
#include "controller/fileManager.h"

//用assimp加载mesh文件
void Model::loadModel(std::string path)
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

  fileExtension = FLOAD::getFileExtension(path);
  directory = path.substr(0, path.find_last_of('/'));
  directory += "/";

  //处理加载的模型
  if (scene != nullptr)
  {
    processNode(scene->mRootNode, scene);
  }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
  //处理所有的节点mesh
  for (unsigned int i = 0; i < node->mNumChildren; i++)
  {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh,scene));
  }



}

//获取所有的顶点数据，获取它们的网格索引，并获取相关的材质数据
//利用三个数据构成一个Mesh对象返回到调用者
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<unsigned int> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    //处理顶点位置、法线、切线、双切线、纹理坐标
    Vertex vertex;
    glm::vec3 vector;

    //Process position
    vector.x = mesh->mVertices[i].x;
    vector.x = mesh->mVertices[i].y;
    vector.x = mesh->mVertices[i].z;
    vertex.position = vector;

    //Process tangent
    vector.x = mesh->mTangents[i].x;
    vector.y = mesh->mTangents[i].y;
    vector.z = mesh->mTangents[i].z;
    vertex.tangent = vector;

    //Process biTangent
    vector.x = mesh->mBitangents[i].x;
    vector.y = mesh->mBitangents[i].y;
    vector.z = mesh->mBitangents[i].z;
    vertex.biTangent = vector;

    //Process normals
    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.normal = vector;

    //Process texture coords
    if (mesh->HasTextureCoords(0)) 
    {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vec;
    }
    else 
    {
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }

  //Process material and texture info
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
  textures = processTextures(material);

  return Mesh(vertices, indices, textures);

}