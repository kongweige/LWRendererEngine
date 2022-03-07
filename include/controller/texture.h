#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

struct Texture
{

  void loadTexture(const std::string& filePath, bool sRGB);

  //����δ��ʼ��ʱidΪ0
  unsigned int textureID = 0;
  int width, height, nComponents;

  std::string type, path;
};

#endif // !TEXTURE_H
