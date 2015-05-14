#pragma once
#include <string>
class DebugPrint
{
public:
	DebugPrint(void);
	virtual ~DebugPrint(void);

	//若定义DEBUG，则输出str，输出以回车结尾
	static void print(std::string str);
};





