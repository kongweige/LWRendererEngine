#include "controller/fileManager.h"
#include <sys/stat.h>
#include <sys/types.h>

//检查文件是否存在并可以读取
bool FLOAD::checkFileValidity(const std::string& filePath) {
  struct stat info;
  //file is blocking access or read 
  if (stat(filePath.c_str(), &info) != 0) 
  {
    printf("Cannot access %s\n", filePath.c_str());
    return false;
  }
  //file is accessible
  else if (info.st_mode & S_IFMT) 
  {
    printf("%s is a valid file\n", filePath.c_str());
    return true;
  }
  //File does not exist
  else 
  {
    printf("Error! File: %s does not exist.\n", filePath.c_str());
    return false;
  }
}

std::string FLOAD::getFileExtension(const std::string& filePath)
{
  size_t indexLocation = filePath.rfind('.', filePath.length());
  if (indexLocation != std::string::npos)
  {
    return filePath.substr(indexLocation + 1, filePath.length() - indexLocation);
  }
  return "";
}



