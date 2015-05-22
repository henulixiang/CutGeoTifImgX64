#include "TileInfo.h"
#include <algorithm>
#include <iostream>
#include <io.h>
#include "ImgInfo.h"
#include <algorithm>
TileInfo::TileInfo(void)
{}
TileInfo::~TileInfo(void)
{}
//构造函数
//img：原始图像的指针
//tileFloor：瓦片层数
TileInfo::TileInfo(ImgInfo *img, int tileFloor):
	img_(img), tileFloor_(tileFloor)
{}
//根据根路径、瓦片层数、文件夹、文件，生成瓦片路径
//rootPath：根路径
//dir：文件夹名字
//file:文件名字
bool TileInfo::createTileFilePath(std::string rootPath, int dir, int file)
{
	char tileFileDir[256];
	sprintf_s(tileFileDir, "%s\\%d\\%d", rootPath.c_str(), this->tileFloor_, dir);
	//目录不存在，则创建
	if(_access(tileFileDir, 0) == -1)
	{
		char createDirCmd[256];
		memset(createDirCmd, 0, sizeof(createDirCmd));
		sprintf_s(createDirCmd, "cmd /c md %s", tileFileDir);
		system(createDirCmd);
	}
	char filePath[256];
	sprintf_s(filePath, "%s\\%d.png", tileFileDir, file);
	this->filePath_ = filePath;
	return true;
}
//根据文件夹、文件的名字计算瓦片左下角点的坐标（相对于左上角，以像素为单位）
//若计算出的坐标不在原始图像范围内，返回原始图像内距该坐标最近的坐标
//dirName：文件夹名字
//fileName：文件名字
//返回值coord：该瓦片左下角的坐标
Pixcoord TileInfo::calcuTileCoord(int dirName, int fileName)
{
	Pixcoord coord;
	double pointLongitude, pointLatitude;
	pointLongitude = img_->calcuTilePixLongitude(dirName, this->tileFloor_);
	pointLatitude = img_->calcuTilePixLatitude(fileName, this->tileFloor_);

	img_->Projection2ImageRowCol(pointLongitude, pointLatitude, coord);

	/*coord.setWidth(MIN(coord.getWidth(), img_->getSrcImgWidth() ) );
	coord.setWidth(MAX(coord.getWidth(), 0) );
	coord.setHeight(MIN(coord.getHeight(), img_->getSrcImgHeigh() ) );
	coord.setHeight(MAX(coord.getHeight(), 0) );*/
	return coord;
}
//获取该文件在原始图像上对应的区域，计算后：
//this->widthPixPoint_保存该区域左上角的宽坐标
//this->heightPixPoint_保存该区域左上角的宽坐标
//this->cutHeightPixLen_保存该区域的高度
//this->cutWidthPixLen_保存该区域的宽度
//dirName:文件夹名字
//fileName：文件名字
//算出坐标返回true，没算出返回false，pix存储最后计算出的结果
bool TileInfo::findPixcoord(int dirName, int fileName, Pixcoord &pix)
{
	Pixcoord tileCoord[2];
	Pixcoord rtn;
	tileCoord[0] = this->calcuTileCoord(dirName, fileName);
	tileCoord[1] = this->calcuTileCoord(dirName + 1, fileName + 1);

	if(tileCoord[0].getHeight() >= img_->getSrcImgHeigh() && tileCoord[1].getHeight() >= img_->getSrcImgHeigh()
		|| tileCoord[0].getHeight() <= 0 && tileCoord[1].getHeight() <= 0
		||tileCoord[0].getWidth() >= img_->getSrcImgWidth() && tileCoord[1].getWidth() >= img_->getSrcImgWidth()
		||tileCoord[0].getWidth() <= 0 && tileCoord[1].getWidth() <= 0)
	{
		return false;
	}
	//若原始图像在缩略图中的大小小于缩略图大小的1/3，则不生成该图
	if(img_->getSrcImgHeigh() < abs(tileCoord[0].getHeight() - tileCoord[1].getHeight() ) / 3 
		|| img_->getSrcImgWidth() < abs(tileCoord[0].getWidth() - tileCoord[1].getWidth() ) / 3 )
	{
		return false;
	}

	this->cutHeightPixLen_ = abs(tileCoord[0].getHeight() - tileCoord[1].getHeight() );
	this->cutWidthPixLen_ = abs(tileCoord[0].getWidth() - tileCoord[1].getWidth() );

	this->widthPixPoint_ = MIN(tileCoord[0].getWidth(), tileCoord[1].getWidth() );
	this->heightPixPoint_ = MAX(tileCoord[0].getHeight(), tileCoord[1].getHeight() );
	
	pix.setWidth(this->widthPixPoint_);
	pix.setHeight(this->heightPixPoint_);
	return true;
	//return Pixcoord(this->widthPixPoint_, this->heightPixPoint_);
}
//返回瓦片路径
std::string TileInfo::getTilePath()
{
	return this->filePath_;
}
