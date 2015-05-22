#pragma once
#include <string>
#include "Pixcoord.h"
#include "ImgInfo.h"
class TileInfo
{
public:
	TileInfo(void);
	virtual ~TileInfo(void);
	//构造函数
	//img：原始图像的指针
	//tileFloor：瓦片层数
	TileInfo(ImgInfo *img, int tileFloor);
	//返回瓦片路径
	std::string getTilePath();
//获取该文件在原始图像上对应的区域，计算后：
//this->widthPixPoint_保存该区域左上角的宽坐标
//this->heightPixPoint_保存该区域左上角的宽坐标
//this->cutHeightPixLen_保存该区域的高度
//this->cutWidthPixLen_保存该区域的宽度
//dirName:文件夹名字
//fileName：文件名字
//算出坐标返回true，没算出返回false，pix存储最后计算出的结果
bool TileInfo::findPixcoord(int dirName, int fileName, Pixcoord &pix);
	//根据根路径、瓦片层数、文件夹、文件，生成瓦片路径
	//rootPath：根路径
	//dir：文件夹名字
	//file:文件名字
	bool createTileFilePath(std::string rootPath, int dir, int file);

	int getWidthPixPoint()
	{
		return this->widthPixPoint_;
	}
	int getHeightPixPoint()
	{
		return this->heightPixPoint_;
	}
	int getCutWidthPixLen()
	{
		return this->cutWidthPixLen_;
	}
	int getCutHeightPixLen()
	{
		return this->cutHeightPixLen_;
	}
private:
	//根据文件夹、文件的名字计算瓦片左下角点的坐标（相对于左上角，以像素为单位）
	//若计算出的坐标不在原始图像范围内，返回原始图像内距该坐标最近的坐标
	//dirName：文件夹名字
	//fileName：文件名字
	//返回值coord：该瓦片左下角的坐标
	Pixcoord calcuTileCoord(int dirName, int fileName);
	//原始图像
	ImgInfo *img_;
	//瓦片路径
	std::string filePath_;
	//瓦片层数
	int tileFloor_;
	//瓦片左下角在原图上的宽坐标
	int widthPixPoint_;
	//瓦片左下角在原图上的高坐标
	int heightPixPoint_;
	//瓦片在原图中宽坐标方向上的大小（以像素为单位）
	int cutWidthPixLen_;
	//瓦片在原图中高坐标方向上的大小（以像素为单位）
	int cutHeightPixLen_;
};

