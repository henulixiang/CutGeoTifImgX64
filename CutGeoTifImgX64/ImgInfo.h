#pragma once
#include "gdal.h"
#include "gdal_alg.h"
#include "ogr_srs_api.h"
#include "cpl_string.h"
#include "cpl_conv.h"
#include "cpl_multiproc.h"
#include "gdal_priv.h"
#include "cpl_vsi.h"
#include "ogr_spatialref.h"
#include "vrtdataset.h"
#include "commonutils.h"
#include <iostream>
#include <string>
#include "Pixcoord.h"
class ImgInfo
{
public:
	ImgInfo(void);
	ImgInfo(std::string srcImgPath);
	//以只读方式打开原始图像，成功：true，失败：false
	void openImg(std::string srcImgPath);
//	bool getPixelLongLat(int widthPoint, int heightPoint);
	virtual ~ImgInfo(void);
	int getSrcImgHeigh();
	int getSrcImgWidth();
	GDALDataset*& getDataset();
//	double convertLongLat2double(const std::string& longORlat);
	//获取任意一个点的经纬度
	//hDataset：图像的GDALDatasetH对象
	//widthPoint：像素的宽坐标
	//heightPoint：像素的纵坐标
	//longttude：计算出的经度，格式：291d 4'34.58''E
	//latitude：计算出的纬度格式：22d17'28.73''S
//	void transCoord2longitudeLatitude(double widthPoint, double heightPoint,std::string &longitude, std::string &latitude);

	//切图，读取原始图像，切指定区域的矩形，生成目标图
	//outImgPath：目标图像的路径（可以是jpg图）
	//widthPoint：切分区域左上角的横坐标（以像素为单位）
	//heightPoint：切分区域左上角的纵坐标（以像素为单位）
	//widthPixelLen：切分区域横坐标上的长度（以像素为单位）
	//heightPixelLen：切分区域纵坐标上的长度（以像素为单位）
	int translate(std::string outImgPath, std::string widthPoint, std::string heightPoint, std::string widthPixelLen, std::string heightPixelLen);
	double getImgMaxLongitude();
	double getImgMinLongitude();
	double getImgMaxLatitude();
	double getImgMinLatitude();
	//根据瓦片左上角的经度和层数计算文件夹的名字
	int calcuTileDirName(double pixLongitude, int tileFloor);
	//根据瓦片左上角的纬度和层数计算文件的名字
	int calcuTileFileName(double pixLatitude, int tileFloor);
	//根据瓦片文件夹的名字和层数计算瓦片左上角的经度
	double calcuTilePixLongitude(int tileDirName, int tileFloor);
	//根据瓦片文件的名字和层数计算瓦片左上角的纬度
	double calcuTilePixLatitude(int tileFileName, int tileFloor);

	

	//根据经纬度找图像上对应的点
	bool Projection2ImageRowCol(double longitude, double latitude, Pixcoord &coord)  ;
	//计算图像上点的经纬度
	bool ImageRowCol2Projection(int width, int height, double &longitude, double &latitude) ;

	int translate(std::string outImgPath, int widthPoint, int heightPoint, int widthPixelLen, int heightPixelLen);
private:
	//计算原始图像的经纬度范围，结果保存到类属性里
	void calcuLongitudeLatitudeRange();

	void CopyBandInfo( GDALRasterBand * poSrcBand, GDALRasterBand * poDstBand,
                          int bCanCopyStatsMetadata, int bCopyScale, int bCopyNoData );

	void AttachMetadata( GDALDatasetH hDS, char **papszMetadataOptions );

	int ArgIsNumeric( const char *pszArg );

	int ProxyMain(int argc, char ** argv );

	int FixSrcDstWindow( int* panSrcWin, int* panDstWin,
                            int nSrcRasterXSize,
                            int nSrcRasterYSize );

	void SrcToDst( double dfX, double dfY,
                      int nSrcXOff, int nSrcYOff,
                      int nSrcXSize, int nSrcYSize,
                      int nDstXOff, int nDstYOff,
                      int nDstXSize, int nDstYSize,
                      double &dfXOut, double &dfYOut );

	void Usage(const char* pszErrorMsg, int bShort);

	//bool GDALInfoReportCorner(OGRCoordinateTransformationH hTransform,
 //                     double x, double y , std::string &longitude, std::string &latitude);
	//原始图像的Dataset
	GDALDataset *srcImgDataset_;
	//原始图像的宽
	int srcImgWidth_;
	//原始图形的高
	int srcImgHigh_;
	//原始图像的波段数
	int srcImgBandCnt_;
	//原始图形的路径
	std::string srcImgPath_;
	//pointCoordinate 
	int bSubCall;
	//整个图片经纬度的范围
	double imgMaxLongitude;
	double imgMinLongitude;
	double imgMaxLatitude;
	double imgMinLatitude;

};
//定义一个坐标点
typedef struct pointCoordinate{
	double abscissa;
	double ordinate;		 
};

enum
{
    MASK_DISABLED,
    MASK_AUTO,
    MASK_USER
};

#define CHECK_HAS_ENOUGH_ADDITIONAL_ARGS(nExtraArg) \
    do { if (i + nExtraArg >= argc) \
        Usage(CPLSPrintf("%s option requires %d argument(s)", argv[i], nExtraArg)); } while(0)


typedef struct
{
    int     bScale;
    int     bHaveScaleSrc;
    double  dfScaleSrcMin, dfScaleSrcMax;
    double  dfScaleDstMin, dfScaleDstMax;
} ScaleParams;