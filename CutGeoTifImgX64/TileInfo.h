#pragma once
#include <string>
#include "Pixcoord.h"
#include "ImgInfo.h"
class TileInfo
{
public:
	TileInfo(void);
	virtual ~TileInfo(void);
	//
	TileInfo(ImgInfo *img, int tileFloor, int widthPixLen, int heightPixLen);
	std::string getTilePath();
	Pixcoord findPixcoord(int dirName, int fileName);
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
	//计算瓦片左上角在原始图像中的坐标（以像素为单位）
	Pixcoord calcuTileCoord(int dirName, int fileName);
	//以二分查找的方式在low和height中找出一个值，该值大于等于small，小于等于big
	//返回-1代表失败
	int binarySearchPixHeightCoord(int low, int height, int small, int big);
	int binarySearchPixWidthCoord(int low, int height, int small, int big);
	ImgInfo *img_;
	//瓦片路径
	std::string filePath_;
	int tileFloor_;
	//瓦片左下角在原图上的点坐标
	int widthPixPoint_;
	int heightPixPoint_;
	//瓦片在原图中的大小
	int cutWidthPixLen_;
	int cutHeightPixLen_;
};

