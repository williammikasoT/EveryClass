// 1.包括json_vc71_libmtd.lib在项目文件夹下 2.设置属性：在MFC中使用静态库
#pragma once
#include "include\json\json.h"
#include<fstream>
#include <string>
#pragma comment(lib,"json_vc71_libmtd.lib")

class JsonClass
{
public:
	JsonClass();
	~JsonClass();
	Json::Value GetJsonFromFile(const char* fileName);
	Json::Value ReadJson(std::string strS);
};

