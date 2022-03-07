#include <glad/glad.h>
#include "controller/texture.h"
#include "controller/fileManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <algorithm>

void Texture::loadTexture(const std::string& filePath, bool sRGB)
{
  path = filePath;
  std::replace(path.begin(), path.end(), '\\', '/');
  std::string fileExtension = FLOAD::getFileExtension(filePath);

  //dds纹理文件
  if (fileExtension == "dds")
  {
    //textureID = loadDDSTexture(path.c_str());
  }
  //加载其他普通纹理图像
  else
  {
    unsigned int ID;
    glGenTextures(1, &ID);
    
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nComponents, 0);
    if (data)
    {
      GLenum format;
      GLenum internalFormat;
      if (nComponents == 1)
      {
        format = GL_RED;
        internalFormat = GL_RED;
      }
      else if (nComponents == 3)
      {
        format = GL_RGB;
        if (sRGB)
        {
          internalFormat = GL_SRGB;
        }
        else
        {
          internalFormat = GL_RGB;
        }
      }
      else if (nComponents == 4)
      {
        format = GL_RGBA;
        if (sRGB) 
        {
          internalFormat = GL_SRGB_ALPHA;
        }
        else 
        {
          internalFormat = GL_RGBA;
        }
      }
      
      glBindTexture(GL_TEXTURE_2D, ID);
      glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(data);
    }
    else
    {
      printf("Texture failed to load at path: %s \n", path.c_str());
    }
    textureID = ID;
  }
}
