
#ifndef MESH_H
#define MESH_H

#include "controller/shader.h"

#include "glm/glm.hpp"
#include <string>

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 tangent;
  glm::vec3 biTangent;
  glm::vec2 texCoords;
};

struct Mesh
{

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<unsigned int> textures;

  Mesh(const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices,
    const std::vector<unsigned int>& textures)
  {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
  }

  //≥ı ºªØª∫≥Â
  void setupMesh();

  //ªÊ÷∆mesh
  void Draw(const Shader &shader, bool textured);

};


#endif // !MESH_H
