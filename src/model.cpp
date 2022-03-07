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

  //递归处理所有子节点
  for (unsigned int i = 0; i < node->mNumChildren; i++) 
  {
    processNode(node->mChildren[i], scene);
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

//获取纹理位置，加载并生成纹理，将纹理ID存储到vector中
std::vector<unsigned int> Model::processTextures(const aiMaterial* material)
{
  std::vector<unsigned int> textures;

  //查找当前纹理路径
  aiString texturePath;
  aiTextureType type;
  std::string fullTexturePath;  //储存纹理的路径用于与其它纹理进行比较

  //遍历所有纹理类型
  for (int tex_index = aiTextureType_NONE; tex_index <= aiTextureType_UNKNOWN; tex_index++)
  {
    type = static_cast<aiTextureType>(tex_index); //索引值转换为enum值
    fullTexturePath = directory;

    //如果有这个纹理
    if (material->GetTextureCount(type) > 0)
    {
      //记录纹理路径 避免多次加载纹理
      material->GetTexture(type, 0, &texturePath);
      fullTexturePath = fullTexturePath.append(texturePath.C_Str());

      //如果纹理不存在则加载它
      //return 成功为1 失败为0
      if (textureAtlas.count(fullTexturePath) == 0)
      {
        Texture texture;
        bool srgb = false;
        texture.loadTexture(fullTexturePath, srgb);
        textureAtlas.insert({ fullTexturePath,texture });
      }

      textures.push_back(textureAtlas.at(fullTexturePath).textureID);
    }
    else
    {
      //For now we always assume that these textures will exist in the current
      //material. If they do not, we assign 0 to their value.
      //This will be fixed when the new material model is implemented.
      switch (type)
      {
      case aiTextureType_LIGHTMAP:
      case aiTextureType_EMISSIVE:
      case aiTextureType_NORMALS:
      case aiTextureType_UNKNOWN:
        textures.push_back(0);
        break;
      }
    }
  }
  return textures;
}

