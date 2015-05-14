#include "DebugPrint.h"
#include <iostream>
#define DEBUG

void DebugPrint::print(std::string str)
{
#ifdef DEBUG
	std::cout << str << std::endl;
#endif // DEBUG
}

DebugPrint::DebugPrint(void)
{
}


DebugPrint::~DebugPrint(void)
{
}
