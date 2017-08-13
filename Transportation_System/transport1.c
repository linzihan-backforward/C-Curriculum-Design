#include"transport1.h"
#include"resource.h"
proute head=NULL;
bool getRouteData(_In_ HWND hdlg, _In_ WPARAM wParam,_Out_ proute temp) {
	TCHAR s[50];
	GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取路线编号
	wcscpy(temp->routNum, s);
	GetDlgItemTextW(hdlg, IDC_EDIT2, s, 50);//获取路线名称
	wcscpy(temp->routName, s);
	GetDlgItemTextW(hdlg, IDC_EDIT3, s, 50);//获取包含站点数
	if ((temp->hasStation = _wtoi(s)) <= 0) {
		MessageBox(hdlg, L"输入包含站点数类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT4, s, 50);//获取距离起始站点距离
	if ((temp->howLong = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入总公里数类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT5, s, 50);//获取距离起始站点距离
	if ((temp->fullTime = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入总耗时类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT7, s, 50);//获取起始站点编号
	wcscpy(temp->startStation, s);
	GetDlgItemTextW(hdlg, IDC_EDIT8, s, 50);//获取终止站点编号
	wcscpy(temp->endStation, s);
	GetDlgItemTextW(hdlg, IDC_EDIT9, s, 50);//获取负责人姓名
	wcscpy(temp->chargePeople, s);
	GetDlgItemTextW(hdlg, IDC_EDIT10, s, 50);//获取负责人办公电话
	wcscpy(temp->chargeTele, s);
	GetDlgItemTextW(hdlg, IDC_EDIT11, s, 50);//获取负责人移动电话
	wcscpy(temp->chargeMobile, s);
	GetDlgItemTextW(hdlg, IDC_EDIT12, s, 50);//获取负责人电子邮箱
	wcscpy(temp->chargeEmail, s);
	temp->headStation = NULL; temp->nextRoute = NULL;
	return true;
}
bool getStationData(_In_ HWND hdlg, _In_ WPARAM wParam, _Out_ pstation temp) {
	TCHAR s[50];
	GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取站点所属路线编号
	wcscpy(temp->belongRoute, s);
	GetDlgItemTextW(hdlg, IDC_EDIT2, s, 50);//获取站点序号
	if ((temp->stationCounter = _wtoi(s)) <= 0) {
		MessageBox(hdlg, L"输入站点序号类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT3, s, 50);//获取站点编号
	wcscpy(temp->stationNum, s);
	GetDlgItemTextW(hdlg, IDC_EDIT4, s, 50);//获取站点名称
	wcscpy(temp->stationName, s);
	GetDlgItemTextW(hdlg, IDC_EDIT5, s, 50);//获取距离起始站点距离
	if ((temp->fromStart = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距起始站点距离类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT6, s, 50);//获取距离上一站点距离
	if ((temp->fromUpper = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距上一站点距离类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT7, s, 50);//获取距离上一站点时间
	if ((temp->fromUpperTime = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距上一站点时间类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT8, s, 50);//获取停留耗时
	if ((temp->stayTime = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入停留耗时类型错误，请重新输入", L"错误", 0);
		return false;
	}
	temp->headTruck = NULL; temp->nextStation = NULL;
	return true;
}
bool getStationData2(_In_ HWND hdlg, _In_ WPARAM wParam, _Out_ pstation temp,TCHAR *previous) {
	TCHAR s[50];
	GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取站点所属路线编号
	wcscpy(temp->belongRoute, s);
	GetDlgItemTextW(hdlg, IDC_EDIT2, s, 50);//获取站点序号
	if ((temp->stationCounter = _wtoi(s)) <= 0) {
		MessageBox(hdlg, L"输入站点序号类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT3, s, 50);//获取站点编号
	wcscpy(temp->stationNum, s);
	GetDlgItemTextW(hdlg, IDC_EDIT4, s, 50);//获取站点名称
	wcscpy(temp->stationName, s);
	GetDlgItemTextW(hdlg, IDC_EDIT5, s, 50);//获取距离起始站点距离
	if ((temp->fromStart = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距起始站点距离类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT6, s, 50);//获取距离上一站点距离
	if ((temp->fromUpper = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距上一站点距离类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT7, s, 50);//获取距离上一站点时间
	if ((temp->fromUpperTime = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入距上一站点时间类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT8, s, 50);//获取停留耗时
	if ((temp->stayTime = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入停留耗时类型错误，请重新输入", L"错误", 0);
		return false;
	}
	GetDlgItemTextW(hdlg, IDC_EDIT9, s, 50);//获取前一个站点
	wcscpy(previous, s);
	temp->headTruck = NULL; temp->nextStation = NULL;
	return true;
}
bool getTruckData(_In_ HWND hdlg, _In_ WPARAM wParam, _Out_ ptruck temp) {
	TCHAR s[50];
	GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取车辆牌照
	wcscpy(temp->truckNum, s);
	GetDlgItemTextW(hdlg, IDC_EDIT2, s, 50);//获取配送路线编号
	wcscpy(temp->belongRoute, s);
	GetDlgItemTextW(hdlg, IDC_EDIT3, s, 50);//获取所属站点编号
	wcscpy(temp->belongStation, s);
	GetDlgItemTextW(hdlg, IDC_EDIT4, s, 50);//获取司机姓名
	wcscpy(temp->driverName, s);
	GetDlgItemTextW(hdlg, IDC_EDIT5, s, 50);//获取司机移动电话
	wcscpy(temp->driverTele, s);
	GetDlgItemTextW(hdlg, IDC_EDIT6, s, 50);//获取本站点载/卸货种类
	wcscpy(temp->load.loadName, s);
	GetDlgItemTextW(hdlg, IDC_EDIT7, s, 50);//获取本站点载/卸货数量
	if ((temp->load.loadWeight = _wtof(s)) <= 0) {
		MessageBox(hdlg, L"输入本站点载/卸货数量类型错误，请重新输入", L"错误", 0);
		return false;
	}
	temp->nextTruck = NULL;
	return true;
}
bool insertStation(pstation nowStation) {
	pstation pr = (pstation)malloc(sizeof(station));
	copyStation(pr,nowStation);
	proute tail = head;
	bool flag = false;
	while (tail != NULL) {
		if (wcscmp(tail->routNum,pr->belongRoute)==0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				if (ps->nextStation == NULL) break;
				else ps = ps->nextStation;
			}
			if (ps == NULL) tail->headStation = pr;
			else {
				ps->nextStation = pr;
				pr->nextStation=NULL;
			}
			flag = true;
		}
		tail = tail->nextRoute;
	}
	if (!flag) {
		free(pr);
		return false;
	}
	else return true;
}
bool insertStation2(pstation nowStation,TCHAR *previous) {
	pstation pr = (pstation)malloc(sizeof(station));
	copyStation(pr, nowStation);
	proute tail = head;
	bool flag = false;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, pr->belongRoute) == 0) {
			pstation ps = tail->headStation;
			if (ps == NULL) {
				tail->headStation = pr;
				flag = true;
				break;
			}
			while (ps != NULL) {
				if (wcscmp(ps->stationNum, previous) == 0) break;
				ps = ps->nextStation;
			}
			if (ps == NULL) {
				return false;
			}
			pr->nextStation=ps->nextStation  ;
			ps->nextStation = pr;
			flag = true;
		}
		tail = tail->nextRoute;
	}
	if (!flag) {
		free(pr);
		return false;
	}
	else return true;
}
bool insertRoute(proute nowRoute) {
	proute pr = (proute)malloc(sizeof(route));
	copyRoute(pr,nowRoute);
	if (head == NULL) 
		head = pr;
	else {
		pr->nextRoute = head;
		head = pr;
	}
		return true;
}
bool insertTruck(ptruck nowTruck) {
	ptruck pr = (ptruck)malloc(sizeof(truck));
	copyTruck(pr,nowTruck);
	bool flag = false;
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, pr->belongRoute) == 0){
			pstation prs = tail->headStation;
			while (prs != NULL) {
				if (wcscmp(prs->stationNum, pr->belongStation) == 0) 
				{
					if (prs->headTruck == NULL) prs->headTruck = pr;
					else {
						pr->nextTruck = prs->headTruck;
						prs->headTruck = pr;
					}
					flag = true;
				}
				prs = prs->nextStation;
			}
		}
		tail = tail->nextRoute;
	}
	if (!flag) {
		free(pr);
		return false;
	}
	else return true;
}
bool changeRoute(proute nowRoute) {
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowRoute->routNum) == 0) {
			nowRoute->nextRoute = tail->nextRoute;
			nowRoute->headStation = tail->headStation;
			copyRoute(tail, nowRoute);
			break;
		}
		tail = tail->nextRoute;
	}
	if (tail == NULL) return false;
	else return true;
}
bool changeStation(pstation nowStation) {
	proute tail = head;
	bool flag = false;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowStation->belongRoute) == 0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				if (wcscmp(ps->stationNum, nowStation->stationNum) == 0) {
					nowStation->nextStation = ps->nextStation;
					nowStation->headTruck = ps->headTruck;
					copyStation(ps, nowStation);
					flag = true;//找到了
				}
				ps = ps->nextStation;
			}
		}
		tail = tail->nextRoute;
	}
	if (!flag) return false;
	else return true;
}
bool changeTruck(ptruck nowTruck) {
	proute tail = head;
	bool flag = false;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowTruck->belongRoute) == 0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				if (wcscmp(ps->stationNum, nowTruck->belongStation) == 0) {
					ptruck pt = ps->headTruck;
					while (pt != NULL) {
						if (wcscmp(pt->truckNum, nowTruck->truckNum) == 0) {
							nowTruck->nextTruck = pt->nextTruck;
							copyTruck(pt, nowTruck);
							flag = true;//找到了
						}
					}
					pt = pt->nextTruck;
				}
			}
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	if (!flag) return false;
	else return true;
}
void copyRoute(proute rec, proute giv){
	wcscpy(rec->chargeEmail, giv->chargeEmail);
	wcscpy(rec->chargeMobile,giv->chargeMobile);
	wcscpy(rec->chargePeople,giv->chargePeople);
	wcscpy(rec->chargeTele,giv->chargeTele);
	wcscpy(rec->endStation,giv->endStation);
	wcscpy(rec->routName,giv->routName);
	wcscpy(rec->routNum,giv->routNum);
	wcscpy(rec->startStation,giv->startStation);
	rec->fullTime = giv->fullTime;
	rec->hasStation = giv->hasStation;
	rec->howLong = giv->howLong;
	rec->nextRoute = giv->nextRoute;
	rec->headStation = giv->headStation;
}
void copyStation(pstation rec, pstation giv) {
	wcscpy(rec->belongRoute, giv->belongRoute);
	wcscpy(rec->stationName, giv->stationName);
	wcscpy(rec->stationNum,giv->stationNum);
	rec->fromStart = giv->fromStart;
	rec->fromUpper = giv->fromUpper;
	rec->fromUpperTime = giv->fromUpperTime;
	rec->headTruck = giv->headTruck;
	rec->nextStation = giv->nextStation;
	rec->stationCounter = giv->stationCounter;
	rec->stayTime = giv->stayTime;
}
void copyTruck(ptruck rec, ptruck giv) {
	wcscpy(rec->belongRoute,giv->belongRoute);
	wcscpy(rec->belongStation,giv->belongStation);
	wcscpy(rec->driverName,giv->driverName);
	wcscpy(rec->driverTele,giv->driverTele);
	wcscpy(rec->truckNum, giv->truckNum);
	wcscpy(rec->load.loadName,giv->load.loadName);
	rec->load.loadWeight = giv->load.loadWeight;
	rec->nextTruck = giv->nextTruck;
}
bool findRoute(proute nowRoute) {
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowRoute->routNum) == 0) 
			return true;
		tail = tail->nextRoute;
	}
	return false;
}
bool findStation(pstation nowStation) {
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowStation->belongRoute) == 0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				if (wcscmp(ps->stationNum, nowStation->stationNum) == 0) 
					return true;
				ps = ps->nextStation;
			}
		}
		tail = tail->nextRoute;
	}
	return false;
}
bool findTruck(ptruck nowTruck) {
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, nowTruck->belongRoute) == 0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				if (wcscmp(ps->stationNum, nowTruck->belongStation) == 0) {
					ptruck pt = ps->headTruck;
					while (pt != NULL) {
						if (wcscmp(pt->truckNum, nowTruck->truckNum) == 0) 
							return true;
						pt = pt->nextTruck;
					}
				}
				ps = ps->nextStation;
			}
			
		}
		tail = tail->nextRoute;
	}
	return false;
}
bool saveInFile() {
	FILE *out1, *out2, *out3;
	proute p = head;
	pstation pexp = NULL;
	ptruck preg = NULL;
	if ((out1 = fopen("Data\\route.dat", "wb")) == NULL)
		return false;
	if ((out2 = fopen("Data\\station.dat", "wb")) == NULL)
		return false;
	if ((out3 = fopen("Data\\truck.dat", "wb")) == NULL)
		return false;
	while (p != NULL)
	{
		fwrite(p, sizeof(route), 1, out1);
		pexp = p->headStation;
		while (pexp)
		{
			fwrite(pexp, sizeof(station), 1, out2);
			preg = pexp->headTruck;
			while (preg)
			{
				fwrite(preg, sizeof(truck), 1, out3);
				preg = preg->nextTruck;
			}
			pexp = pexp->nextStation;
		}
		p = p->nextRoute;
	}
	fclose(out1);
	fclose(out2);
	fclose(out3);
	return true;
}
bool loadInFile() {
	FILE*in1, *in2, *in3;
	proute hp = NULL, p;
	pstation pexp;
	ptruck preg;
	/*打开三个文件并判断能否正常打开*/
	if ((in1 = fopen("Data\route.dat", "rb")) == NULL)
		return false;
	if ((in2 = fopen("Data\station.dat", "rb")) == NULL)
		return false;
	if ((in3 = fopen("Data\truck.dat", "rb")) == NULL)
		return false;
	while (!feof(in1))/*将存储路线基本信息链的文件调入内存*/
	{
		p = (proute)malloc(sizeof(route));
		fread(p, sizeof(route), 1, in1);
		if (!feof(in1))
		{
			p->headStation = NULL;
			p->nextRoute = hp;
			hp = p;
		}
	}
	head = hp;
	while (!feof(in2))/*将存储站点链的文件调入内存*/
	{
		pexp = (pstation)malloc(sizeof(station));
		fread(pexp, sizeof(station), 1, in2);
		if (!feof(in2))
		{
			p = head;
			while (p != NULL)
			{
				if (!wcscmp(p->routNum, pexp->belongRoute))
				{
					pexp->headTruck = NULL;
					pexp->nextStation = p->headStation;
					p->headStation = pexp;
				}
					p = p->nextRoute;
			}
		}
	}

	while (!feof(in3))/*将存储车辆信息链的文件调入内存*/
	{
		preg = (ptruck)malloc(sizeof(truck));
		fread(preg, sizeof(truck), 1, in3);
		if (!feof(in3))
		{
			p = head;
			while (p != NULL)
			{
				pexp = p->headStation;
				while (pexp && !feof(in3))
				{
					if (!wcscmp(pexp->stationNum, preg->belongStation))
					{
						preg->nextTruck = pexp->headTruck;
						pexp->headTruck = preg;
						preg = (ptruck)malloc(sizeof(truck));
						fread(preg, sizeof(truck), 1, in3);
					}
					else
						pexp = pexp->nextStation;
				}
				p = p->nextRoute;
			}
		}
	}
	return true;
}
bool deleteRoute(TCHAR rNum[]) {
	proute tail = head,previous=head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, rNum) == 0) {
			pstation psv = tail->headStation,ps;
			if (psv == NULL) ps = psv;
			else ps = psv->nextStation;
			while (ps != NULL) {
				ptruck ptv = psv->headTruck, pt;
				if(ptv==NULL) pt= ptv;
				else pt = ptv->nextTruck;
				while (pt != NULL) {
					free(ptv);
					ptv = pt;
					pt = pt->nextTruck;
				}
				free(ptv);
				free(psv);
				psv = ps;
				ps = ps->nextStation;
			}
			if (psv != NULL) {
				ptruck ptv = psv->headTruck, pt;
				if (ptv == NULL) pt = ptv;
				else pt = ptv->nextTruck;
				while (pt != NULL) {
					free(ptv);
					ptv = pt;
					pt = pt->nextTruck;
				}
				free(ptv);
				free(psv);
			}
			if (tail == head) head = tail->nextRoute;
			else previous->nextRoute = tail->nextRoute;
			free(tail);
			return true;
		}
		previous = tail;
		tail = tail->nextRoute;
	}
	return false;
}

bool deleteStation(TCHAR sNum[]) {
	proute tail = head;
	bool flag = false;
	while (tail != NULL) {
		pstation psv = tail->headStation, ps;
		if(psv==NULL)	ps=psv;
		else ps = psv->nextStation;
		while (ps != NULL) {
			if (wcscmp(ps->stationNum, sNum) == 0) {
				if (ps == tail->headStation) tail->headStation = ps->nextStation;
				else psv->nextStation = ps->nextStation;
				ptruck ptv = ps->headTruck,pt;
				if (ptv == NULL) pt = ptv;
				else ptv = pt->nextTruck;
				while (pt != NULL) {
					free(ptv);
					ptv = pt;
					pt = pt->nextTruck;
				}
				if(ptv!=NULL) free(ptv);
				free(ps);
				flag = true;
				break;
			}
			psv = ps;
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	if (!flag) return false;
	else return true;
}
bool deleteTruck(TCHAR tNum[]) {
	bool flag = false;
	proute tail = head;
	while (tail != NULL) {
		pstation ps = tail->headStation;
		while (ps != NULL) {
			ptruck ptv = ps->headTruck, pt;
			if(ptv==NULL) pt= ptv;
			else pt = ptv->nextTruck;
			while (pt != NULL) {
				if (wcscmp(pt->truckNum, tNum) == 0) {
					if (pt == ps->headTruck) {
						ps->headTruck = pt->nextTruck;
						free(pt);
					}
					else {
						ptv->nextTruck = pt->nextTruck;
						free(pt);
					}
					return true;
				}
				ptv = pt;
				pt = pt->nextTruck;
			}
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	 return false;
}
bool searchRouteFromStation(HWND hdlg, TCHAR s[]) {
	TCHAR temp[500]=L"经过此站点的路线如下:\n";
	TCHAR *ans=temp;
	int cnt = 0;
	proute tail = head;
	while (tail != NULL) {
		pstation ps = tail->headStation;
		while (ps != NULL) {
			if (wcscmp(ps->stationNum, s) == 0) {
				cnt++;
				ans = wcscat(ans, tail->routNum);
				ans = wcscat(ans, L"\n");
				break;
			}
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	if (cnt == 0) return false;
	else {
		MessageBox(hdlg, ans, L"查询", MB_OK);
		return true;
	}
	free(temp);
	free(ans);
}
bool searchLongest(HWND hwnd) {
	double minni = 1e10,maxx=-1.0;
	TCHAR minans[10],maxxans[10];
	proute tail = head;
	while (tail != NULL) {
		if (tail->fullTime > maxx) {
			maxx = tail->fullTime;
			wcscpy(maxxans, tail->routNum);
		}
		if (tail->fullTime < minni) {
			minni = tail->fullTime;
			wcscpy(minans, tail->routNum);
		}
		tail = tail->nextRoute;
	}
	if (minni >= 1e10 || maxx < 0) return false;
	TCHAR temp[100] = L"耗时最长路线编号为：\n";
	TCHAR *ans = temp;
	ans = wcscat(ans, maxxans);
	ans = wcscat(ans, L"\n最短路线编号为：\n");
	ans = wcscat(ans, minans);
	MessageBox(hwnd, ans, L"查询", MB_OK);
	return true;
}
bool searchKiloLongest(HWND hwnd) {
	double minni = 1e10, maxx = -1.0;
	TCHAR minans[10], maxxans[10];
	proute tail = head;
	while (tail != NULL) {
		if (tail->howLong > maxx) {
			maxx = tail->howLong;
			wcscpy(maxxans, tail->routNum);
		}
		if (tail->howLong < minni) {
			minni = tail->howLong;
			wcscpy(minans, tail->routNum);
		}
		tail = tail->nextRoute;
	}
	if (minni >= 1e10 || maxx < 0) return false;
	TCHAR temp[100] = L"公里数最长路线编号为：\n";
	TCHAR *ans = temp;
	ans = wcscat(ans, maxxans);
	ans = wcscat(ans, L"\n最短路线编号为：\n");
	ans = wcscat(ans, minans);
	MessageBox(hwnd, ans, L"查询", MB_OK);
	return true;
}
bool findStationByRoute(HWND hwnd,TCHAR s[]) {
	TCHAR temp[500] = L"此路线的站点如下:\n";
	TCHAR *ans = temp;
	int cnt = 0;
	proute tail = head;
	while (tail != NULL) {
		if (wcscmp(tail->routNum, s) == 0) {
			pstation ps = tail->headStation;
			while (ps != NULL) {
				cnt++;
				ans = wcscat(ans, ps->stationNum);
				ans = wcscat(ans, L"\n");
				ps = ps->nextStation;
			}
		}
		tail = tail->nextRoute;
	}
	if (cnt == 0) return false;
	else {
		MessageBox(hwnd, ans, L"查询", MB_OK);
		return true;
	}
	free(temp);
	free(ans);
}
bool findStationByDriver(HWND hdlg, TCHAR s[]) {
	TCHAR temp[500] = L"此司机的配送路线如下:";
	TCHAR *ans = temp;
	int cnt = 0;
	bool flag = true;
	proute tail = head;
	while (tail != NULL) {
		pstation ps = tail->headStation;
		while (ps != NULL) {
			ptruck pt = ps->headTruck;
			while(pt!=NULL){
				if (wcscmp(pt->driverName, s) == 0) {
					cnt++;
					if (flag) {
						ans = wcscat(ans, L"\n路线编号为：");
						ans = wcscat(ans, tail->routNum);
						ans = wcscat(ans, L"中的站点：\n");
						flag = false;
					}
					ans = wcscat(ans, ps->stationNum);
					ans = wcscat(ans, L" ");
				}
				pt = pt->nextTruck;
			}
			ps = ps->nextStation;
		}
		flag = true;
		tail = tail->nextRoute;
	}
	if (cnt == 0) return false;
	else {
		MessageBox(hdlg, ans, L"查询", MB_OK);
		return true;
	}
	free(temp);
	free(ans);
}
bool findTeleByDriver(HWND hdlg, TCHAR s[]) {
	TCHAR temp[500] = L"此司机的电话为:\n";
	TCHAR *ans = temp;
	int cnt = 0;
	proute tail = head;
	while (tail != NULL) {
		pstation ps = tail->headStation;
		while (ps != NULL) {
			ptruck pt = ps->headTruck;
			while (pt != NULL) {
				if (wcscmp(pt->driverName, s) == 0) {
					cnt++;
					ans = wcscat(ans, pt->driverTele);
					break;
				}
				pt = pt->nextTruck;
			}
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	if (cnt == 0) return false;
	else {
		MessageBox(hdlg, ans, L"查询", MB_OK);
		return true;
	}
	free(temp);
	free(ans);
}
bool findStationByTruck(HWND hdlg, TCHAR s[]) {
	TCHAR temp[500] = L"此车辆的配送路线如下:";
	TCHAR *ans = temp;
	int cnt = 0;
	bool flag = true;
	proute tail = head;
	while (tail != NULL) {
		pstation ps = tail->headStation;
		while (ps != NULL) {
			ptruck pt = ps->headTruck;
			while (pt != NULL) {
				if (wcscmp(pt->truckNum, s) == 0) {
					cnt++;
					if (flag) {
						ans = wcscat(ans, L"\n路线编号为");
						ans = wcscat(ans, tail->routNum);
						ans = wcscat(ans, L"中的站点：\n");
						flag = false;
					}
					ans = wcscat(ans, ps->stationNum);
					ans = wcscat(ans, L" ");
				}
				pt = pt->nextTruck;
			}
			ps = ps->nextStation;
		}
		flag = true;
		tail = tail->nextRoute;
	}
	if (cnt == 0) return false;
	else {
		MessageBox(hdlg, ans, L"查询", MB_OK);
		return true;
	}
	free(temp);
	free(ans);
}
void getTable(HWND hdlg) {
	TCHAR temp[1000] = L"所有数据如下:\n";
	TCHAR *ans = temp;
	proute tail = head;
	while (tail != NULL) {
		ans = wcscat(ans, L"线路");
		ans = wcscat(ans, tail->routNum);
		ans = wcscat(ans, L"\n");
		pstation ps = tail->headStation;
		while (ps != NULL) {
			ans = wcscat(ans, L"    ");
			ans = wcscat(ans, L"站点");
			ans = wcscat(ans, ps->stationNum);
			ans = wcscat(ans, L"\n");
			ptruck pt = ps->headTruck;
			while (pt != NULL) {
				ans = wcscat(ans, L"        ");
				ans = wcscat(ans, L"车辆");
				ans = wcscat(ans, pt->truckNum);
				ans = wcscat(ans, L"\n");
				pt = pt->nextTruck;
			}
			ps = ps->nextStation;
		}
		tail = tail->nextRoute;
	}
	MessageBox(hdlg, ans, L"报表", MB_OK);
}