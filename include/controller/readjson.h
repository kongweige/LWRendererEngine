/**
 * @file readjson.h
 * @author 
 * @brief ���ڽ���json�ļ�
 * @version 1.0.0
 * @date 2022-2-16
 *
 */
#include <iostream>
//#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
/**
 * @class ��ȡjson�ļ�
 * �������ڶ�ȡjson�ļ�����ȡ�����ݷ��͸�modelģ��
 */
class ReadJson
{
public:
	ReadJson();
	~ReadJson();
public:

	void test();

private:

};