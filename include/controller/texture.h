#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

struct Texture
{

  void loadTexture(const std::string& filePath, bool sRGB);

  //纹理未初始化时id为0
  unsigned int textureID = 0;
  int width, height, nComponents;

  std::string type, path;
};

#endif // !TEXTURE_H
