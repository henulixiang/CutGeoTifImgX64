//#include <windows.h>   
//#include <iostream>   
//#include <tchar.h>  
//#include "gdal_translate.h"
//#include "cpl_vsi.h"
//#include "cpl_conv.h"
//#include "cpl_string.h"
//#include "gdal_priv.h"
//#include "ogr_spatialref.h"
//#include "vrtdataset.h"
//#include "commonutils.h"
//using namespace std;   
//  
//DWORD BeginTime;   
//LONG ItemCount;   
//HANDLE CompleteEvent;   
//  
//
////CRITICAL_SECTION m_locklixiang;
//
//int lixiang = 0;
//std::string getlixiang()
//{
////	EnterCriticalSection(&m_locklixiang);
//	static int a = 0;
//
//	char outImgPath[100];
//	sprintf(outImgPath, "D:\\GDALTEST\\utm_tiled%ld.jpg", ++a);
////	LeaveCriticalSection(&m_locklixiang);
//	return string(outImgPath);
//}
//  
//GDALDatasetH hDataset;
//int compute()   
//{   
//    /*srand(BeginTime);   
//  
//    for(int i=0; i<20 *1000 * 1000; i++)   
//        rand();   
//  
//    return rand();   */
//	GDALAllRegister();
//	translate("D:\\GDALTEST\\test.jpg" ,getlixiang(), "0", "0", "1632", "1224");
//	//GDALAllRegister();
//	//GDALOpenShared( "D:\\GDALTEST\\test.tif", GA_ReadOnly );
//	cout << "lixiang" << endl;
//	return 0;
//}   
//
//DWORD WINAPI WorkItem(LPVOID lpParameter)   
//{   
//    BOOL bWaitMode = (BOOL)lpParameter;   
//  
//    /*if(bWaitMode)   
//        Sleep(1000);   
//    else  */ 
//        compute();   
//	//print();
//    //cout<<ItemCount<<endl;   
//    if(InterlockedDecrement(&ItemCount) == 0)//保证原子操作   
//    {   
//        cout<<"Time total "<<(GetTickCount() - BeginTime)/1000.0<<" 秒./n"<<endl;   
//        SetEvent(CompleteEvent);   
//    }   
//    return 0;   
//}   
//void TestWorkItem(BOOL bWaitMode, DWORD Flag)   
//{   
//	
//
//
//    CompleteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);   
//    BeginTime = GetTickCount();   
//    ItemCount = 20;   
//    HINSTANCE hInst=LoadLibrary(_T("Kernel32.DLL"));   
//    if(hInst)   
//    {   
//        typedef BOOL(WINAPI * MYFUNC)(LPTHREAD_START_ROUTINE, PVOID,ULONG);   
//        MYFUNC MyQueueUserWorkItem=NULL;   
//  
//        //取得QueueUserWorkItem函数指针   
//        MyQueueUserWorkItem=(MYFUNC)GetProcAddress(hInst,"QueueUserWorkItem");   
//        if(!MyQueueUserWorkItem)   
//        {   
//            MessageBox(NULL, _T("获取函数地址失败","你好!"), _T("错误提示"),  MB_OK);   
//            return;   
//        }   
//  
//        for(int i=0; i<10; i++)   
//        {   
//            MyQueueUserWorkItem(WorkItem, (PVOID)bWaitMode, Flag);   
//        }   
//        FreeLibrary(hInst);   
//    }   
//  
//    WaitForSingleObject(CompleteEvent, INFINITE);   
//	
//    CloseHandle(CompleteEvent);   
//}   
//int main()   
//{//   InitializeCriticalSection(&m_locklixiang);//初始化
//    TestWorkItem(0,WT_EXECUTEINIOTHREAD);   
//    cout<<"工作项目执行完毕!"<<endl;   
//    return 0;   
//}  