#include "Pixcoord.h"

Pixcoord::Pixcoord(void)
{}

Pixcoord::~Pixcoord(void)
{}
//相对于左上角的坐标
Pixcoord::Pixcoord(int width, int height)
{
	this->width_ = width;
	this->height_ = height;
}