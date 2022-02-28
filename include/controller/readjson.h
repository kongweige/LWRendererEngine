/**
 * @file readjson.h
 * @author 
 * @brief 用于解析json文件
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
 * @class 读取json文件
 * 此类用于读取json文件将读取的数据发送给model模块
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