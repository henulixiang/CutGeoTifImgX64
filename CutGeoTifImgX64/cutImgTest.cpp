#include <iostream>
#include "gdal_priv.h"
#include "cpl_conv.h" 
#include "DebugPrint.h"
#include "ImgInfo.h"
#include "TileInfo.h"
#include <io.h>
#include <algorithm>
#include <cmath>
#include <string>
#include "Pixcoord.h"
using namespace std;
/**
* 作者：李想
* 编写日期：2015-05-22
* 修改者：
* 修改日期：
*
* 程序功能：对GeoTiff图像切图，采用TMS算法，目前该算法为串行
* 改成多线程程序非常简单，只需要将main（）中的三个for（）并行就OK
* 并行最简单的方法是采用openMP，三分钟搞定！
*
* 程序思想：首先算出待处理图像的经纬度范围，根据该经纬度范围计算文件夹、拇指图文件的范围
* 根据文件夹、文件的名字，倒推出原始图像中哪块区域对应该拇指图，最后直接找到该区域，将该区域切下即可
*
* 通过文件夹、文件的名字推待切图像区域的方法：首先获得当前文件左下角的经纬度，然后计算右上角的经纬度 
* 通过这两对经纬度的值，找到在待切图像中的坐标，找到后切之！
*
**/
int main(int argc, char* argv[])
{
	GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO"); 
	ImgInfo img("D:\\GDALTEST\\test.tif");

	for(int floor = 1; floor <=17; ++ floor)
	{
		int tileFloor = floor;
		string rootPath("D:\\GDALTEST");

		int dirNameMin = img.calcuTileDirName(img.getImgMinLongitude(), tileFloor);
		int dirNameMax = img.calcuTileDirName(img.getImgMaxLongitude(), tileFloor);
		int fileNameMin = img.calcuTileFileName(img.getImgMinLatitude(), tileFloor);
		int fileNameMax = img.calcuTileFileName(img.getImgMaxLatitude(), tileFloor);

		if(dirNameMin > dirNameMax)
		{
			swap(dirNameMin, dirNameMax);
		}
		if(fileNameMin > fileNameMax)
		{
			swap(fileNameMin, fileNameMax);
		}

		/*int stepWidthLen = (img.getSrcImgWidth() % static_cast<int>( pow(2, tileFloor)) == 0) ?
			(img.getSrcImgWidth() / static_cast<int>( pow(2, tileFloor))) :
			(img.getSrcImgWidth() / static_cast<int>( pow(2, tileFloor)) + 1);
		int stepHeightLen = (img.getSrcImgHeigh() % static_cast<int>( pow(2, tileFloor)) == 0) ? 
			(img.getSrcImgHeigh() / static_cast<int>( pow(2, tileFloor))) : 
			(img.getSrcImgHeigh() / static_cast<int>( pow(2, tileFloor)) + 1);*/

		for(int dirName = dirNameMin; dirName <= dirNameMax; ++ dirName )
		{
			for(int fileName = fileNameMin; fileName <= fileNameMax; ++ fileName)
			{
				TileInfo tile(&img, tileFloor);
				Pixcoord pix;
				if(!tile.findPixcoord(dirName, fileName, pix) )
				{
					continue;
				}

				if(tile.getCutWidthPixLen() <= 0 || tile.getCutHeightPixLen() <= 0 || tile.getHeightPixPoint() <= 0)
				{
					continue;
				}
				tile.createTileFilePath(rootPath, dirName, fileName);
				img.translate(tile.getTilePath(), tile.getWidthPixPoint(), tile.getHeightPixPoint() - tile.getCutHeightPixLen(), 
					tile.getCutWidthPixLen(), tile.getCutHeightPixLen() );
			}
		}
	}
	return 0;
}
