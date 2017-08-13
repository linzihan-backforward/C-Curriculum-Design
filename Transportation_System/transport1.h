#pragma once
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<wingdi.h>
#include<stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct Route {
	TCHAR routNum[6];//路线编号
	TCHAR routName[20];//路线名称
	int hasStation;//包含的总站点数
	double howLong;//总公里数
	double fullTime;//总耗时（包括站点停留时间）
	TCHAR startStation[10];//起始站点编号
	TCHAR endStation[10];//结束站点编号
	TCHAR chargePeople[30];//负责人姓名
	TCHAR chargeTele[8];//负责人办公电话
	TCHAR chargeMobile[11];//负责人移动电话
	TCHAR chargeEmail[50];//负责人电子邮箱
	struct Station* headStation;//站点链表
	struct Route* nextRoute;//链表next指针

}route,*proute;
typedef struct Station {
	TCHAR belongRoute[6];//所属路线编号
	int stationCounter;//站点序号
	TCHAR stationNum[10];//站点编号
	TCHAR stationName[50];//站点名称
	double fromStart;//距离起始站点距离
	double fromUpper;//距离上一个站点距离
	double fromUpperTime;//与上一个站点交通耗时
	double stayTime;//停留时间
	struct Truck *headTruck;//车辆链表
	struct Station *nextStation;//链表next指针
}station,*pstation;
typedef struct Truck {
	TCHAR truckNum[8];//车辆牌照
	TCHAR belongRoute[6];//执行的配送路线编号
	TCHAR driverName[30];//司机姓名
	TCHAR driverTele[11];//司机移动电话
	TCHAR belongStation[10];//所属站点编号
	struct StationLoad {
		TCHAR loadName[20];//本站点载/卸货种类
		double loadWeight;//本站点载/卸货重量
	}load;
	struct Truck * nextTruck;//链表next指针
}truck,*ptruck;
extern proute head;//十字交叉链表总头指针

bool getRouteData(_In_ HWND hdlg,_In_ WPARAM wParam,_Out_ proute temp);//获取路线输入
bool getStationData(_In_ HWND hdlg,_In_ WPARAM wParam, _Out_ pstation temp);//获取站点输入
bool getTruckData(_In_ HWND hdlg, _In_ WPARAM wParam, _Out_ ptruck temp);//获取车辆输入
bool getStationData2(_In_ HWND hdlg, _In_ WPARAM wParam, _Out_ pstation temp, TCHAR *previous);//获取添加站点的输入
bool insertRoute(proute nowRoute);//添加一个路线
bool insertStation(pstation nowStation);//添加一个站点
bool insertStation2(pstation nowStation, TCHAR *previous);//在previous后增加一个站点
bool insertTruck(ptruck nowTruck);//添加一个车辆
bool changeRoute(proute nowRoute);//修改一个路线
bool changeStation(pstation nowStation);//修改一个站点
bool changeTruck(ptruck nowTruck);//修改一个车辆
void copyRoute(proute rec, proute giv);//复制一个路线
void copyStation(pstation rec, pstation giv);//复制一个站点
void copyTruck(ptruck rec, ptruck giv);//复制一个车辆
bool findRoute(proute nowRoute);//找一个路线
bool findStation(pstation nowStation);//找一个站点
bool findTruck(ptruck nowTruck);//找一个车辆
bool saveInFile();//数据存入文件
bool loadInFile();//数据从文件中读取
bool deleteRoute(TCHAR rNum[]);//删除路线
bool deleteStation(TCHAR sNum[]);//删除站点
bool deleteTruck(TCHAR tNum[]);//删除车辆
bool searchRouteFromStation(HWND hdlg,TCHAR s[]);//查询经过一个站点的所有车辆
bool searchLongest(HWND hwnd);//查询耗时最长和最短的路线
bool searchKiloLongest(HWND hwnd);//查询公里数最长或最短的路线
bool findStationByRoute(HWND hwnd,TCHAR s[]);//查询制定路线的所有
bool findStationByDriver(HWND hdlg, TCHAR s[]);//查询制定司机的配送路线
bool findTeleByDriver(HWND hdlg, TCHAR s[]);//查询指定司机的联系方式
bool findStationByTruck(HWND hdlg, TCHAR s[]);//查询指定车辆的配送路线
void getTable(HWND hdlg);//输出报表