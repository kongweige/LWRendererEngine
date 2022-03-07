#include "controller/model.h"
#include <string>
#include "controller/fileManager.h"

//��assimp����mesh�ļ�
void Model::loadModel(std::string path)
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

  fileExtension = FLOAD::getFileExtension(path);
  directory = path.substr(0, path.find_last_of('/'));
  directory += "/";

  //������ص�ģ��
  if (scene != nullptr)
  {
    processNode(scene->mRootNode, scene);
  }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
  //�������еĽڵ�mesh
  for (unsigned int i = 0; i < node->mNumChildren; i++)
  {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh,scene));
  }

  //�ݹ鴦�������ӽڵ�
  for (unsigned int i = 0; i < node->mNumChildren; i++) 
  {
    processNode(node->mChildren[i], scene);
  }
}

//��ȡ���еĶ������ݣ���ȡ���ǵ���������������ȡ��صĲ�������
//�����������ݹ���һ��Mesh���󷵻ص�������
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<unsigned int> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    //������λ�á����ߡ����ߡ�˫���ߡ���������
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

//��ȡ����λ�ã����ز���������������ID�洢��vector��
std::vector<unsigned int> Model::processTextures(const aiMaterial* material)
{
  std::vector<unsigned int> textures;

  //���ҵ�ǰ����·��
  aiString texturePath;
  aiTextureType type;
  std::string fullTexturePath;  //���������·������������������бȽ�

  //����������������
  for (int tex_index = aiTextureType_NONE; tex_index <= aiTextureType_UNKNOWN; tex_index++)
  {
    type = static_cast<aiTextureType>(tex_index); //����ֵת��Ϊenumֵ
    fullTexturePath = directory;

    //������������
    if (material->GetTextureCount(type) > 0)
    {
      //��¼����·�� �����μ�������
      material->GetTexture(type, 0, &texturePath);
      fullTexturePath = fullTexturePath.append(texturePath.C_Str());

      //������������������
      //return �ɹ�Ϊ1 ʧ��Ϊ0
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

