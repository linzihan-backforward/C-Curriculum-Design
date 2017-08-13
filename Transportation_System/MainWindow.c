#include"MainWindow.h"
#include"resource.h"
#include"transport1.h"

HINSTANCE hInst;
#define _CRT_SECURE_NO_WARNINGS
int CALLBACK WinMain(//入口函数
	_In_ HINSTANCE hInstance,//当前应用实例句柄
	_In_ HINSTANCE hPrevInstance,//上一个应用实例句柄
	_In_ LPSTR lpCmdLine,//命令行参数
	_In_ int nCmdShow//显示方式
) {
	WNDCLASS mainWindow;
	mainWindow.cbClsExtra = 0;//通常设为0
	mainWindow.cbWndExtra = 0;
	mainWindow.hCursor = LoadCursor(hInstance, IDC_ARROW);//光标资源
	mainWindow.hIcon = LoadIcon(hInstance, IDI_APPLICATION);//图标资源
	mainWindow.lpszMenuName = NULL;//菜单的ID
	mainWindow.style = CS_HREDRAW | CS_VREDRAW;//窗口类样式
	mainWindow.hbrBackground = (HBRUSH)COLOR_WINDOW;//背景色
	mainWindow.lpfnWndProc = WindowProc;//消息处理函数
	mainWindow.lpszClassName = L"My Class";//类名
	mainWindow.hInstance = hInstance;//实例句柄
	hInst = hInstance;//将当前应用程序句柄赋给全局变量，方便调用
	RegisterClass(&mainWindow);//注册窗口

	HWND hwnd = CreateWindow(//创建窗口
		L"My Class",//类名（与窗口类名一致）
		L"Transport System",//窗口标题文字
		WS_OVERLAPPEDWINDOW,//窗口外观样式
		600,//窗口相对于父级的x坐标
		400,//窗口相对于父级的y坐标
		600,//窗口的宽度
		400,//窗口的高度
		NULL,//有无父窗口
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)),//有无菜单栏
		hInstance,//实例句柄
		NULL);//无附加数据
	if (hwnd != NULL) {//判断是否创建成功
		ShowWindow(hwnd, SW_SHOW);//显示窗口
		UpdateWindow(hwnd);//更新窗口
	}
	else return 0;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {//获取消息
		TranslateMessage(&msg);//转换消息
		DispatchMessage(&msg);//将消息交给相应函数
	}

	return 0;
}
LRESULT CALLBACK WindowProc(//消息响应函数实现
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	HDC			 hdc;             //句柄
	PAINTSTRUCT	 ps;
	RECT			 rect;            //矩形
	switch (uMsg) {
		case WM_PAINT: {//相应重绘消息
			hdc=BeginPaint(hwnd, &ps);
			SetTextColor(hdc, RGB(10, 0, 255));
			GetClientRect(hwnd, &rect);
			rect.left = 20; rect.top = 70; rect.bottom = 250; rect.right = 250;
			DrawText(hdc, L"欢迎使用本系统", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			rect.top += 20; rect.bottom += 20;
			DrawText(hdc, L"使用方法请阅读相关文档", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			rect.left = 0; rect.top = 280; rect.bottom = 310; rect.right = 150;
			DrawText(hdc, L"@copyright:linzihan", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			rect.top += 20; rect.bottom += 20; rect.right += 150;
			DrawText(hdc, L"Open Source At:www.github.com//linzihan", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			HPEN pen = CreatePen(PS_SOLID, 2, RGB(200, 100, 20));//创建笔  
																 // 将笔选到DC中  
			auto oldObj = SelectObject(ps.hdc, pen);
			// 画弧线  
			Arc(hdc, 20, 70, 250, 250, 20, 70, 20, 70);
			//Arc(hdc, 200, 160, 390, 400, 300, 350, 380, 165);
			// 画完之后，把原先的笔选回去  
			SelectObject(hdc, oldObj);
			// 清理  
			DeleteObject(pen);
			HBITMAP hbmp;   //一张位图的句柄  
			BITMAP bmp;

			//hdc = BeginPaint(hwnd, &ps); //为指定句柄hwnd窗口进行绘画准备工作  
			HDC hdcMem;
			hdcMem = CreateCompatibleDC(hdc);  //创建一个与指定设备兼容的内存设备上下文环境  
			hbmp = (HBITMAP)LoadImage(NULL, L"picture/华科校徽.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			
			//if(hbmp!=NULL) MessageBox(hwnd, L"已成功保存", L"提醒", MB_OK | MB_ICONINFORMATION);
			GetObject(hbmp, sizeof(BITMAP), &bmp);  //得到一个位图对象  
			
			SelectObject(hdcMem, hbmp);
			StretchBlt(hdc, 380, 0, bmp.bmWidth/4*3, bmp.bmHeight/4*3, hdcMem,0,0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);        //显示位图  

			DeleteDC(hdcMem);
			DeleteObject(hbmp);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CREATE: {
			CreateWindow(L"Button", L"退出", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
				400, 280, 160, 60, hwnd, (HMENU)IDB_ONE, hInst, NULL);
		}
		return 0;
		case WM_COMMAND: {//响应用户点击消息
			switch (LOWORD(wParam)) {
				case IDM_40001://添加-添加路线
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DIALOG1);
					break;
				case IDM_40002://添加-添加站点
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, DIALOG2);
					break;
				case IDM_40003://添加-添加车辆
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, DIALOG3);
					break;
				case ID_40007://录入
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, DIALOG4);
					break;
				case ID_40008: {//录入-保存全部
					//此处添加保存到文件的操作
					if(saveInFile())
						MessageBox(hwnd, L"已成功保存",L"提醒", MB_OK | MB_ICONINFORMATION);
					else MessageBox(hwnd, L"保存失败", L"提醒", MB_OK | MB_ICONINFORMATION);
					break;
				}
				case ID_40009://修改-修改路线
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hwnd, DIALOG7);
					break;
				case ID_40010://修改-修改站点
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hwnd, DIALOG8);
					break;
				case ID_40011://修改-修改车辆
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hwnd, DIALOG9);
					break;
				case ID_40012://删除-删除路线
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG10), hwnd, DIALOG10);
					break;
				case ID_40013://删除-删除站点
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG11), hwnd, DIALOG11);
					break;
				case ID_40014://删除-删除车辆
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG12), hwnd, DIALOG12);
					break;
				case ID_40017: {//查询-报表
					getTable(hwnd);
					
					break; 
				}
				case ID_40018: {//查询-	查询经停某站点的所有路线
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG13), hwnd, DIALOG13);
					break; 
				}
				case ID_40019: {//查询-	查询耗时最长及最短的路线
					if(!searchLongest(hwnd))
						MessageBox(hwnd, L"错误", L"错误", MB_OK | MB_ICONINFORMATION);

					break;
				}
				case ID_40020: {//查询-		查询路线公里数最长及最短的路线
					if (!searchKiloLongest(hwnd))
						MessageBox(hwnd, L"错误", L"错误", MB_OK | MB_ICONINFORMATION);
					break;
				}
				case ID_40021: {//查询-			查询指定路线的所有经停站点
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG14), hwnd, DIALOG14);
					break;
				}
				case ID_40023: {//查询-			查询指定司机的配送清单
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG15), hwnd, DIALOG15);

					break;
				}
				case ID_40024: {//查询-			查询指定车辆的司机联系方式
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG16), hwnd, DIALOG16);

					break;
				}
				case ID_40025: {//查询-			查询指定车辆的配送路线
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG17), hwnd, DIALOG17);

					break;
				}
				case ID_40026: {//录入-			从文件中录入
					if (loadInFile())
						MessageBox(hwnd, L"已成功读取", L"提醒", MB_OK | MB_ICONINFORMATION);
					else MessageBox(hwnd, L"读取失败", L"提醒", MB_OK | MB_ICONINFORMATION);

					break;
				}
				case IDB_ONE: {//主界面退出button
					DestroyWindow(hwnd);
					break;
				}
				default: break;
			}
			break;
		}
		case WM_DESTROY: {//相应退出消息
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
INT_PTR CALLBACK DIALOG1(//添加一条路线、对话框响应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			route temp;
			if (getRouteData(hdlg,wParam,&temp))
				if(!findRoute(&temp)&&insertRoute(&temp)) {
					MessageBox(hdlg, L"已成功添加", L"提示", MB_OK);
					EndDialog(hdlg, LOWORD(wParam));
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG2(//添加一个站点、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if ( LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			station temp; TCHAR previous[10];
			if (getStationData2(hdlg,wParam,&temp,previous))
				if(!findStation(&temp)&&insertStation2(&temp,previous)) {
					MessageBox(hdlg, L"已成功添加", L"提示", MB_OK);
					EndDialog(hdlg, LOWORD(wParam));
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG3(//添加一个车辆、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			truck temp;
			if (getTruckData(hdlg,wParam,&temp))
				if(!findTruck(&temp)&&insertTruck(&temp)) {
					MessageBox(hdlg, L"已成功添加", L"提示", MB_OK);
					EndDialog(hdlg, LOWORD(wParam));
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {

			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG4(//录入信息一级对话框
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			route temp;
			if (getRouteData(hdlg, wParam, &temp) &&(!findRoute(&temp))&& insertRoute(&temp)) {
				MessageBox(hdlg, L"已成功录入", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1) {
			route temp;
			if (getRouteData(hdlg, wParam, &temp) ){ 
				if (!findRoute(&temp) && insertRoute(&temp)) {
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hdlg, DIALOG4);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			return(INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON2) {
			route temp;
			if (getRouteData(hdlg, wParam, &temp) ){
				if (!findRoute(&temp) && insertRoute(&temp)) {
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hdlg, DIALOG5);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			return(INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG5(//录入信息二级对话框
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			station temp;
			if (getStationData(hdlg, wParam, &temp)) {
				if (!findStation(&temp) && insertStation(&temp)) {
					MessageBox(hdlg, L"已成功录入", L"提示", MB_OK);
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hdlg, DIALOG4);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			return (INT_PTR)TRUE;
		}

		
		if (LOWORD(wParam) == IDC_BUTTON22) {
			station temp;
			if (getStationData(hdlg, wParam, &temp)) {
				if (!findStation(&temp) && insertStation(&temp)) {
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hdlg, DIALOG5);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}

			return(INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON11) {
			station temp;
			if (getStationData(hdlg, wParam, &temp)) {
				if (!findStation(&temp) && insertStation(&temp)) {
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hdlg, DIALOG6);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			else  MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			return(INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG6(//录入信息三级对话框
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			truck temp;
			if (getTruckData(hdlg, wParam, &temp)){ 
				if (!findTruck(&temp) && insertTruck(&temp)) {
					MessageBox(hdlg, L"已成功录入", L"提示", MB_OK);
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hdlg, DIALOG5);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON31) {
			truck temp;
			if (getTruckData(hdlg, wParam, &temp) ){
				if (!findTruck(&temp) && insertTruck(&temp)) {
					EndDialog(hdlg, LOWORD(wParam));
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hdlg, DIALOG6);
				}
				else MessageBox(hdlg, L"信息错误", L"提示", MB_OK);
			}
			
			return(INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG7(//修改一个路线、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if ( LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			route temp;
			if (getRouteData(hdlg, wParam, &temp) && changeRoute(&temp)) {
				MessageBox(hdlg, L"已成功修改", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG8(//修改一个站点、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			station temp;
			if (getStationData(hdlg, wParam, &temp) && changeStation(&temp)) {
				MessageBox(hdlg, L"已成功修改", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"修改失败，请检查输入数据", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG9(//修改一个车辆、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			truck temp;
			if (getTruckData(hdlg, wParam, &temp) && changeTruck(&temp)) {
				MessageBox(hdlg, L"已成功修改", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"修改失败，请检查输入数据", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG10(//删除一条路线、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			//添加删除代码
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取要删除的路线编号
			if (deleteRoute(s)) {
				MessageBox(hdlg, L"已成功删除", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此路线", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG11(//删除一个站点、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			//添加删除代码
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取要删除的站点编号
			if (deleteStation(s)) {
				MessageBox(hdlg, L"已成功删除", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此站点", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG12(//删除一个车辆、对话框相应函数
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			//添加删除代码
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取要删除的车辆编号
			if (deleteTruck(s)) {
				MessageBox(hdlg, L"已成功删除", L"提示", MB_OK);
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此车辆", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG13(//查询-查询经过某站点的所有路线
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取站点编号
			if (searchRouteFromStation(hdlg,s)) {
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此站点", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG14(//查询-查询经过某站点的所有路线
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取路线编号
			if (findStationByRoute(hdlg, s)) {
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此路线", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG15(//查询-查询指定司机的配送清单
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取司机姓名
			if (findStationByDriver(hdlg, s)) {
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此司机", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG16(//查询-查询指定司机的配送清单
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取司机姓名
			if (findTeleByDriver(hdlg, s)) {
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此司机", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK DIALOG17(//查询-查询指定车辆的配送清单
	_In_ HWND hdlg,
	_In_ UINT msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {
			TCHAR s[50];
			GetDlgItemTextW(hdlg, IDC_EDIT1, s, 50);//获取车辆牌照
			if (findStationByTruck(hdlg, s)) {
				EndDialog(hdlg, LOWORD(wParam));
			}
			else MessageBox(hdlg, L"无此车辆", L"提示", MB_OK);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}