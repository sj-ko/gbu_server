// GBU_Server.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GBU_Server.h"

// Modules
#include "MediaServer.h"
#include "Database.h"
#include "anpr.h"

#include <Commctrl.h> // ListView
#include <Windows.h> // Timechecker

#define USE_ANPR
#define MAX_LOADSTRING 100

// Global Variables:
const int g_windowWidth = 600;
const int g_windowHeight = 250;

// Time checker
LARGE_INTEGER g_frequency;

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND g_hWnd;

HANDLE g_hEventThread;
DWORD g_dwEventThreadId;
BOOL g_bEventThreadRunFlag;

#define MAX_CAMERA_NUM	3
VideoCapture g_camera_frame[MAX_CAMERA_NUM];

double g_camera_frame_count[MAX_CAMERA_NUM]; // negative, if streaming
const char g_cv_window_name[MAX_CAMERA_NUM][64] = { ("Video Test1"), ("Video Test2"), ("Video Test3") };
const char g_anpr_window_name[] = ("ANPR Area");
const wchar_t g_default_url[MAX_CAMERA_NUM][1024] = {
	TEXT("C:\\Work\\SNB-7004_192.168.0.18_80-Cam01_H.264_1920X1080_fps_30_20150327_142030.avi"),
	TEXT("C:\\Work\\SNZ-5200_192.168.0.44_4520-Cam01_H.264_1280X1024_fps_30_20150327_050004.avi"),
	TEXT("C:\\Work\\SNZ-5200_192.168.0.44_4520-Cam01_H.264_1280X1024_fps_30_20150327_050858.avi"),
};
//const wchar_t g_default_url[] = TEXT("rtsp://test:test1234@1.233.158.28:554/Streaming/Channels/101?transportmode=unicast");


HANDLE g_hMediaThread[MAX_CAMERA_NUM];
DWORD g_dwMediaThreadId[MAX_CAMERA_NUM];
BOOL g_bMediaThreadRunFlag[MAX_CAMERA_NUM];


Database* g_database;

#ifdef USE_ANPR
cmAnpr* g_anprmodule;
#endif // USE_ANPR

HWND g_hEditURL[MAX_CAMERA_NUM];
HWND g_hConnectButton[MAX_CAMERA_NUM];
HWND g_hDisconnectButton[MAX_CAMERA_NUM];
HWND g_hCameraControlButton;
HWND g_hLogButton;
HWND g_hLogDialog;

BOOL g_is_left_button_down = FALSE;
Rect g_drag_rect;

struct Anpr_log {
	// Thumbnail
	BITMAP thumb;

	// Plate
	string plate;

	// Time
	DWORD dwTime;

	// Etc
	string etc;
};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK	LogProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK CameraDialogProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI MediaThreadFunction(LPVOID lpParam);
DWORD WINAPI EventThreadFunction(LPVOID lpParam);

void onOpenCVMouse(int evt, int x, int y, int flags, void* param);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GBU_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GBU_SERVER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GBU_SERVER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GBU_SERVER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; // WS_OVERLAPPEDWINDOW - (WS_MAXIMIZEBOX + WS_THICKFRAME)

	hInst = hInstance; // Store instance handle in our global variable

	g_hWnd = CreateWindow(szWindowClass, szTitle, windowStyle,
		CW_USEDEFAULT, 0, g_windowWidth, g_windowHeight, NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
	{
		return FALSE;
	}

	// Event Thread
	g_bEventThreadRunFlag = TRUE;
	g_hEventThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		EventThreadFunction,       // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&g_dwEventThreadId);

	// Additional Init
	g_database = new Database(NULL);
	g_database->GetCameraList();

	QueryPerformanceFrequency((LARGE_INTEGER *)&g_frequency);

#ifdef USE_ANPR
	OutputDebugString(TEXT("Set ANPR module..."));
	g_anprmodule = new cmAnpr("default");
	OutputDebugString(TEXT("OK\nInit ANPR module..."));
	initANPR(g_anprmodule);
	OutputDebugString(TEXT("OK\n"));

	//Sets an engine, that can read empty ADR plates
	OutputDebugString(TEXT("Printing ANPR module info..."));
	gxOutStrArray properties = g_anprmodule->GetEngineProperties(true);
	for (int i = 0; i < properties.size(); i++)
	{
		gxOutStr str = properties[i];
		str.append(TEXT("\n"));
		OutputDebugString(str.c_str());
	}
	OutputDebugString(TEXT("OK\n"));
#endif // USE_ANPR

	// Start Application
	g_drag_rect = Rect(0, 0, 0, 0);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

void StartVideo(wchar_t* szURL, int index)
{
	char szURL_multibyte[1024];
	ConvertWCtoC(szURL, szURL_multibyte, 1023);
	if (g_camera_frame[index].isOpened())
		g_camera_frame[index].release();

	g_camera_frame[index] = VideoCapture(szURL_multibyte);
	g_camera_frame_count[index] = g_camera_frame[index].get(CAP_PROP_FRAME_COUNT);

	g_bMediaThreadRunFlag[index] = TRUE;
	g_hMediaThread[index] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MediaThreadFunction,       // thread function name
		&index,          // argument to thread function 
		0,                      // use default creation flags 
		&g_dwMediaThreadId[index]);

	namedWindow(g_cv_window_name[index], WINDOW_NORMAL);
	//namedWindow(g_anpr_window_name, WINDOW_NORMAL);
	setMouseCallback(g_cv_window_name[index], onOpenCVMouse, NULL);
}

void ReleaseVideo(int index, BOOL showBlank = TRUE)
{
	g_drag_rect = Rect(0, 0, 0, 0);

	if (showBlank == FALSE) {
		destroyAllWindows();
	}

	// Media Thread
	g_bMediaThreadRunFlag[index] = FALSE;
	WaitForSingleObject(g_hMediaThread[index], INFINITE);
	CloseHandle(g_hMediaThread[index]);
	g_hMediaThread[index] = NULL;

	if (g_camera_frame[index].isOpened())
		g_camera_frame[index].release();

	// Show Black window
	if (showBlank) {
		Mat blank = Mat::zeros(100, 100, CV_8UC1);
		imshow(g_cv_window_name[index], blank);
		//imshow(g_anpr_window_name, blank);
	}
}

void ReleaseModules()
{
	if (g_database)
		delete g_database;

#ifdef USE_ANPR
	if (g_anprmodule)
		delete g_anprmodule;
#endif // USE_ANPR

	for (int i = 0; i < MAX_CAMERA_NUM; i++)
		ReleaseVideo(i, FALSE);
}

void InitDialogUI(HWND hWnd)
{
	// Edit Box for URL
	g_hEditURL[0] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"),
		g_default_url[0], WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL,
		20, 10, 460, 30, hWnd, (HMENU)IDC_MAIN_EDIT_URL1, GetModuleHandle(NULL), NULL);
	g_hConnectButton[0] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Connect"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		490, 10, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_CONNECT1, GetModuleHandle(NULL), NULL);
	g_hDisconnectButton[0] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Disconnect"), WS_CHILD | WS_TABSTOP,
		490, 10, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_DISCONNECT1, GetModuleHandle(NULL), NULL);

	g_hEditURL[1] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"),
		g_default_url[1], WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL,
		20, 50, 460, 30, hWnd, (HMENU)IDC_MAIN_EDIT_URL2, GetModuleHandle(NULL), NULL);
	g_hConnectButton[1] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Connect"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		490, 50, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_CONNECT2, GetModuleHandle(NULL), NULL);
	g_hDisconnectButton[1] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Disconnect"), WS_CHILD | WS_TABSTOP,
		490, 50, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_DISCONNECT2, GetModuleHandle(NULL), NULL);

	g_hEditURL[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"),
		g_default_url[2], WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL,
		20, 90, 460, 30, hWnd, (HMENU)IDC_MAIN_EDIT_URL3, GetModuleHandle(NULL), NULL);
	g_hConnectButton[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Connect"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		490, 90, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_CONNECT3, GetModuleHandle(NULL), NULL);
	g_hDisconnectButton[2] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Disconnect"), WS_CHILD | WS_TABSTOP,
		490, 90, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_DISCONNECT3, GetModuleHandle(NULL), NULL);

	g_hCameraControlButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Camera"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		20, 130, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_CAMERA, GetModuleHandle(NULL), NULL);
	g_hLogButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Log"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		105, 130, 80, 30, hWnd, (HMENU)IDC_MAIN_BUTTON_LOG, GetModuleHandle(NULL), NULL);

	g_hLogDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_LOG), hWnd, LogProc);
	if (g_hLogDialog)
	{
		RECT Rect;
		GetWindowRect(hWnd, &Rect);
		MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT)&Rect, 2);

		SetWindowPos(g_hLogDialog, NULL, Rect.left, Rect.top + g_windowHeight + 5, 0, 0, SWP_NOSIZE);

		ShowWindow(g_hLogDialog, SW_SHOW);
		UpdateWindow(g_hLogDialog);
	}
}

void ConnectCamera(HWND hWnd, int index)
{
	HWND hConnectButton = g_hConnectButton[index];;
	HWND hDisconnectButton = g_hDisconnectButton[index];
	int nDialogItemID = 0;

	switch (index) {
	case 0:
		nDialogItemID = IDC_MAIN_EDIT_URL1;
		break;
	case 1:
		nDialogItemID = IDC_MAIN_EDIT_URL2;
		break;
	case 2:
		nDialogItemID = IDC_MAIN_EDIT_URL3;
		break;
	default:
		return;
	}

	EnableWindow(hConnectButton, FALSE);

	wchar_t szURL[1024] = { 0, };
	if (GetDlgItemText(hWnd, nDialogItemID, szURL, 1023)) {
		ShowWindow(hConnectButton, SW_HIDE);
		ShowWindow(hDisconnectButton, SW_SHOW);

		StartVideo(szURL, index);
	}

	EnableWindow(hConnectButton, TRUE);
}

void DisconnectCamera(int index)
{
	HWND hConnectButton = g_hConnectButton[index];
	HWND hDisconnectButton = g_hDisconnectButton[index];

	ShowWindow(hDisconnectButton, SW_HIDE);
	ShowWindow(hConnectButton, SW_SHOW);

	ReleaseVideo(index);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		InitDialogUI(hWnd);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_MAIN_BUTTON_CONNECT1:
			ConnectCamera(hWnd, 0);
			break;
		case IDC_MAIN_BUTTON_CONNECT2:
			ConnectCamera(hWnd, 1);
			break;
		case IDC_MAIN_BUTTON_CONNECT3:
			ConnectCamera(hWnd, 2);
			break;
		case IDC_MAIN_BUTTON_DISCONNECT1:
			DisconnectCamera(0);
			break;
		case IDC_MAIN_BUTTON_DISCONNECT2:
			DisconnectCamera(1);
			break;
		case IDC_MAIN_BUTTON_DISCONNECT3:
			DisconnectCamera(2);
			break;
		case IDC_MAIN_BUTTON_CAMERA:
			if (DialogBox(hInst,
				MAKEINTRESOURCE(IDD_DIALOG_CAMERA),
				hWnd,
				(DLGPROC)CameraDialogProc) == IDOK)
			{
				// Modal Window
			}
			break;
		case IDC_MAIN_BUTTON_LOG:
			ShowWindow(g_hLogDialog, SW_SHOW);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if (MessageBox(hWnd, TEXT("Do you really want to close the server program?"), TEXT("Quit"), MB_OKCANCEL) == IDOK)
				DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Do you really want to close the server program?"), TEXT("Quit"), MB_OKCANCEL) == IDOK)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		ReleaseModules();
		DestroyWindow(g_hLogDialog);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void SetLog(Mat& image, wchar_t* plate, wchar_t* msg)
{
	Mat vflip, resizeImg;
	flip(image, vflip, 0);
	resize(vflip, resizeImg, Size(200, 200));

	unsigned char* pBuffer = resizeImg.data;

	tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)pBuffer;
	tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(pBuffer + sizeof(tagBITMAPFILEHEADER));
	RGBQUAD             rgb = *(RGBQUAD*)(pBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER));

	BITMAPINFO bmInfo;
	ZeroMemory(&bmInfo, sizeof(BITMAPINFO));
	bmInfo.bmiHeader.biBitCount = 24;
	bmInfo.bmiHeader.biHeight = resizeImg.rows;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = resizeImg.cols;
	bmInfo.bmiHeader.biCompression = BI_RGB;

	char* ppvBits;
	HANDLE hBitmap;
	hBitmap = CreateDIBSection(NULL, &bmInfo, DIB_RGB_COLORS, (void**)&ppvBits, NULL, 0);
	memcpy(ppvBits, resizeImg.data, resizeImg.rows*resizeImg.cols * 3);

	HWND hPic = GetDlgItem(g_hLogDialog, IDC_STATIC_THUMB);
	if (hPic){
		DWORD dw = 0;
		SendMessageTimeout(hPic, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap), SMTO_NORMAL, 1000, &dw);
	}

	HWND hPlate = GetDlgItem(g_hLogDialog, IDC_STATIC_PLATE);
	SetWindowText(hPlate, plate);
}

BOOL CALLBACK LogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	HWND hWndListView = GetDlgItem(hWnd, IDC_LIST_LOG);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		Mat original = imread("C:\\Users\\Terry\\Pictures\\face.jpg");
		Mat vflip, test;
		flip(original, vflip, 0);
		resize(vflip, test, Size(200, 200));

		unsigned char* pBuffer = test.data;

		tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)pBuffer;
		tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(pBuffer + sizeof(tagBITMAPFILEHEADER));
		RGBQUAD             rgb = *(RGBQUAD*)(pBuffer + sizeof(tagBITMAPFILEHEADER) + sizeof(tagBITMAPINFOHEADER));

		BITMAPINFO bmInfo;
		ZeroMemory(&bmInfo, sizeof(BITMAPINFO));
		bmInfo.bmiHeader.biBitCount = 24;
		bmInfo.bmiHeader.biHeight = test.rows;
		bmInfo.bmiHeader.biPlanes = 1;
		bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth = test.cols;
		bmInfo.bmiHeader.biCompression = BI_RGB;

		char* ppvBits;
		HANDLE hBitmap;
		hBitmap = CreateDIBSection(NULL, &bmInfo, DIB_RGB_COLORS, (void**)&ppvBits, NULL, 0);
		memcpy(ppvBits, test.data, test.rows*test.cols * 3);

		HWND hPic = GetDlgItem(hWnd, IDC_STATIC_THUMB);
		SendMessage(hPic, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));



		// Initialize Columns
		LVCOLUMN lvc = { 0 };
		INT nSubItem = 0;
		HWND hWndHdr = NULL;
		INT nCount = 0;

		const LPTSTR lpszTitle[] = { TEXT("Image"), TEXT("Plate"), TEXT("Time"), TEXT("Etc.") };

		nCount = sizeof(lpszTitle) / sizeof(LPCTSTR);
		hWndHdr = ListView_GetHeader(hWndListView);
		//Header_SetImageList(hWndHdr, g_himl);

		/* Initialize the LVCOLUMN structure. */
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.iImage = 0;
		lvc.cx = 100;

		for (nSubItem = 0; nSubItem < nCount; ++nSubItem) {
			lvc.iSubItem = nSubItem;
			lvc.pszText = lpszTitle[nSubItem];
			lvc.fmt = LVCFMT_LEFT;
			ListView_InsertColumn(hWndListView, lvc.iSubItem, &lvc);
		}
	}
		break;
	case WM_NOTIFY:
	{
		NMLVDISPINFO* plvdi;

		switch (((LPNMHDR)lParam)->code)
		{
		case LVN_GETDISPINFO:

			plvdi = (NMLVDISPINFO*)lParam;

			switch (plvdi->item.iSubItem)
			{
			case 0: // Image
				plvdi->item.pszText = TEXT("A");
				break;
			case 1: // Plate
				plvdi->item.pszText = TEXT("B");
				break;
			case 2: // Time
				plvdi->item.pszText = TEXT("C");
				break;
			case 3: // Etc.
				plvdi->item.pszText = TEXT("D");
				break;
			default:
				break;
			}

			break;

		}
	}
		break;
	case WM_CLOSE:
		//insert test
	{
		LVITEM lvI;

		// Initialize LVITEM members that are common to all items.
		lvI.pszText = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvI.stateMask = 0;
		lvI.iSubItem = 0;
		lvI.state = 0;

		// Initialize LVITEM members that are different for each item.
		for (int index = 0; index < 1; index++)
		{
			lvI.iItem = index;
			lvI.iImage = index;


			// Insert items into the list.
			if (ListView_InsertItem(hWndListView, &lvI) == -1)
				return FALSE;
		}
	}

		//ShowWindow(hWnd, SW_HIDE);
		break;
	}
	return FALSE;
}

// Camera Dialog
BOOL CALLBACK CameraDialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			//if (!GetDlgItemText(hwndDlg, ID_ITEMNAME, szItemName, 80))
			//	*szItemName = 0;
			MessageBox(hwndDlg, TEXT("Test"), TEXT("Caption"), MB_OK);
			// Fall through. 

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		}
	}
	return FALSE;
}

void onOpenCVMouse(int evt, int x, int y, int flags, void* param)
{
	static POINT startPoint = { 0, };
	static Rect drag_rect = Rect(0, 0, 0, 0);
	//SampleClass *p = (SampleClass *)param;
	if (evt == CV_EVENT_MOUSEMOVE)
	{
		if (g_is_left_button_down) {
			int currentwidth = abs(x - startPoint.x);

			if ((currentwidth & 0x3) == 0x0) {
				drag_rect.x = MIN(x, startPoint.x);
				drag_rect.y = MIN(y, startPoint.y);
				drag_rect.width = currentwidth;
				drag_rect.height = abs(y - startPoint.y);

				g_drag_rect = drag_rect;
			}
		}
	}
	else if (evt == CV_EVENT_LBUTTONDOWN)
	{
		g_is_left_button_down = TRUE;

		startPoint.x = x;
		startPoint.y = y;
	}
	else if (evt == CV_EVENT_LBUTTONUP)
	{
		g_is_left_button_down = FALSE;

		wchar_t current_rect[64];
		wsprintf(current_rect, TEXT("Rect: %d x %d\n"), g_drag_rect.width, g_drag_rect.height);
		OutputDebugString(current_rect);
	}
	else if (evt == CV_EVENT_RBUTTONDOWN)
	{
		// Reset
		g_drag_rect = Rect(0, 0, 0, 0);
	}
}

// Event ThreadFunction
DWORD WINAPI MediaThreadFunction(LPVOID lpParam)
{
	//PMYDATA pDataArray = (PMYDATA)lpParam;
	int* pCameraIndex = (int*)lpParam;
	int i = *pCameraIndex;

	Mat frame;
	if (g_camera_frame_count[i] > 0) {
		// Video File mode
		int64 prev_frame_time, curr_frame_time;
		QueryPerformanceCounter((LARGE_INTEGER *)&prev_frame_time);


		while (g_bMediaThreadRunFlag[i]) {

			if (g_camera_frame[i].isOpened()) {
				if (g_camera_frame[i].read(frame)) {

					// Push Media
					GBUVideoFrame thisframe;
					thisframe.frame = frame;
					thisframe.camindex = i;

					while (true)
					{
						QueryPerformanceCounter((LARGE_INTEGER *)&curr_frame_time);

						int64 elapsed = curr_frame_time - prev_frame_time;
						double duringtime = (double)elapsed / (double)g_frequency.QuadPart;
						if (duringtime > 0.03)
							break;
						else
							Sleep(1);
					}

					push_media(thisframe);
				}
				else {
					// Repeat Video
					g_camera_frame[i].set(CAP_PROP_POS_FRAMES, 0);
				}
			}

			Sleep(1);
		}
	}
	else {
		// Real camera mode
		while (g_bMediaThreadRunFlag[i]) {

			if (g_camera_frame[i].isOpened()) {
				if (g_camera_frame[i].read(frame)) {

					// Push Media
					GBUVideoFrame thisframe;
					thisframe.frame = frame;
					thisframe.camindex = i;

					push_media(thisframe);
				}
			}

			Sleep(1);
		}
	}

	return 0;
}

// Media ThreadFunction
DWORD WINAPI EventThreadFunction(LPVOID lpParam)
{
	//PMYDATA pDataArray = (PMYDATA)lpParam;
#ifdef USE_ANPR
	std::vector<PLATE_CANDIDATE> plate_candidates;
	gxImage croppedimage("default");
	std::vector<std::wstring> anpr_result;
#endif // USE_ANPR

	DWORD dwLastShowInterval[MAX_CAMERA_NUM] = { 0, };
	int64 starttime, endtime;

	GBUVideoFrame frame;
	Mat cropregion;
	while (g_bEventThreadRunFlag) {

		if (pop_media(&frame)){
			// ANPR Here
			if (g_drag_rect.width != 0 && g_drag_rect.height != 0) {

#ifdef USE_ANPR
				if (g_is_left_button_down == FALSE) {
					// gxImage only support 4 times width
					if (g_drag_rect.width != croppedimage.xsize() || g_drag_rect.height != croppedimage.ysize()) {
						croppedimage.Create(GX_BGR, g_drag_rect.width, g_drag_rect.height, 0);
					}
					cropregion = frame.frame(g_drag_rect).clone();

					int total = cropregion.rows*cropregion.cols*cropregion.elemSize1()*cropregion.channels();
					croppedimage.LoadFromMem(cropregion.data, total, -1); // About 1ms to load

					// Run ANPR
					QueryPerformanceCounter((LARGE_INTEGER *)&starttime);

					anpr_result.clear();
					if (getValidPlates(g_anprmodule, croppedimage, anpr_result) > 0) {

						// Remove old results
						unsigned long currentTime = GetTickCount();
						for (std::vector<PLATE_CANDIDATE>::iterator iter = plate_candidates.begin(); iter != plate_candidates.end();){
							if (currentTime - (*iter).firstfoundTime > CANDIDATE_REMOVE_TIME)
								iter = plate_candidates.erase(iter);
							else
								++iter;
						}

						// Check duplicate
						for (int i = 0; i < anpr_result.size(); i++) {
							bool isNew = true;

							for (int j = 0; j < plate_candidates.size(); j++) {

								if (_tcsnccmp(anpr_result[i].c_str(), plate_candidates[j].plate_string, _tcslen(anpr_result[i].c_str())) == 0)  {
									isNew = false;

									plate_candidates[j].foundCount++;
									if (plate_candidates[j].foundCount == CANDIDATE_COUNT_FOR_PASS) {
										// Announce Event
										SetLog(cropregion, plate_candidates[j].plate_string, TEXT("msg"));

										wchar_t eventlog[1024];
										wsprintf(eventlog, TEXT("%s\t"), plate_candidates[j].plate_string);
										OutputDebugString(eventlog);
									}
									break;
								}
							}

							if (isNew) {
								PLATE_CANDIDATE newItem = { 0, };
								newItem.firstfoundTime = currentTime;
								newItem.foundCount = 1;

								_tcsnccpy(newItem.plate_string, anpr_result[i].c_str(), _tcslen(anpr_result[i].c_str()));

								plate_candidates.push_back(newItem);
							}
						}
					}

					QueryPerformanceCounter((LARGE_INTEGER *)&endtime);

					int64 elapsed = endtime - starttime;
					double duringtime = (double)elapsed / (double)g_frequency.QuadPart;

					wchar_t anpr_elapsed_str[64];
					swprintf(anpr_elapsed_str, TEXT("ANPR Elapsed: %f (%dx%d)\n"), duringtime, g_drag_rect.width, g_drag_rect.height);
					OutputDebugString(anpr_elapsed_str);
				}
#endif // USE_ANPR

				rectangle(frame.frame, g_drag_rect, Scalar(0, 0, 255), 2);
			}

			// Show
			if (cvGetWindowHandle(g_cv_window_name[frame.camindex])) {

#define TIME_JUMP
#ifdef TIME_JUMP
				DWORD dwCurrentTick = GetTickCount();
				if (dwCurrentTick - dwLastShowInterval[frame.camindex] > 1000) {
					imshow(g_cv_window_name[frame.camindex], frame.frame);

					dwLastShowInterval[frame.camindex] = dwCurrentTick;
				}
#else
				imshow(g_cv_window_name[frame.camindex], frame.frame);
#endif
			}
		}

		Sleep(1);
	}

	return 0;
}