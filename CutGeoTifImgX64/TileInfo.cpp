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

TileInfo::TileInfo(ImgInfo *img, int tileFloor, int widthPixLen, int heightPixLen):
	img_(img), tileFloor_(tileFloor)
{}

bool TileInfo::createTileFilePath(std::string rootPath, int dir, int file)
{
	char tileFileDir[256];
	//sprintf(tileFileDir, "%s\\%d\\%d", rootPath.c_str(), this->tileFloor_, dir);
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

Pixcoord TileInfo::calcuTileCoord(int dirName, int fileName)
{
	Pixcoord coord;
	double pointLongitude, pointLatitude;
	pointLongitude = img_->calcuTilePixLongitude(dirName, this->tileFloor_);
	pointLatitude = img_->calcuTilePixLatitude(fileName, this->tileFloor_);

	img_->Projection2ImageRowCol(pointLongitude, pointLatitude, coord);

	coord.setWidth(MIN(coord.getWidth(), img_->getSrcImgWidth() ) );
	coord.setWidth(MAX(coord.getWidth(), 0) );
	coord.setHeight(MIN(coord.getHeight(), img_->getSrcImgHeigh() ) );
	coord.setHeight(MAX(coord.getHeight(), 0) );
	return coord;
}
Pixcoord TileInfo::findPixcoord(int dirName, int fileName)
{
	Pixcoord tileCoord[2];
	Pixcoord rtn;
	tileCoord[0] = this->calcuTileCoord(dirName, fileName);
	tileCoord[1] = this->calcuTileCoord(dirName + 1, fileName + 1);
	
	this->cutHeightPixLen_ = abs(tileCoord[0].getHeight() - tileCoord[1].getHeight() );
	this->cutWidthPixLen_ = abs(tileCoord[0].getWidth() - tileCoord[1].getWidth() );

	this->widthPixPoint_ = MIN(tileCoord[0].getWidth(), tileCoord[1].getWidth() );
	this->heightPixPoint_ = MAX(tileCoord[0].getHeight(), tileCoord[1].getHeight() );
	
	return Pixcoord(this->widthPixPoint_, this->heightPixPoint_);
}

std::string TileInfo::getTilePath()
{
	return this->filePath_;
}
