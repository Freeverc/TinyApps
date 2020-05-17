// Tetris.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
#include "resource.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

int GRID = 30;
int WINDOWX = 400;
int WINDOWY = 100;
int WINDOWHEIGHT = 660;
int LEFTREGIONWIDTH = 360;
int RIGHTREGIONWIDTH = 200;
int WINDOWWIDTH = LEFTREGIONWIDTH + RIGHTREGIONWIDTH;
int BRICKSIZE = LEFTREGIONWIDTH / 12;

int bricks[7][4][4][4] =
{
	{   // I型方块
		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {1, 1, 1, 1},
		 {0, 0, 0, 0}},

		{{0, 0, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0}},

		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {1, 1, 1, 1},
		 {0, 0, 0, 0}},

		{{0, 0, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0},
		 {0, 0, 1, 0}}
	},
	{   // T型方块
		{{0, 0, 0, 0},
		 {0, 0, 2, 0},
		 {0, 2, 2, 2},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 0, 2, 0},
		 {0, 0, 2, 2},
		 {0, 0, 2, 0}},

		{{0, 0, 0, 0},
		 {0, 0, 0, 0},
		 {0, 2, 2, 2},
		 {0, 0, 2, 0}},

		{{0, 0, 0, 0},
		 {0, 0, 2, 0},
		 {0, 2, 2, 0},
		 {0, 0, 2, 0}},
	},
	{   // L型方块
		{{0, 3, 0, 0},
		 {0, 3, 0, 0},
		 {0, 3, 3, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {3, 3, 3, 0},
		 {3, 0, 0, 0},
		 {0, 0, 0, 0}},	

		{{3, 3, 0, 0},
		 {0, 3, 0, 0},
		 {0, 3, 0, 0},
		 {0, 0, 0, 0}},	

		{{0, 0, 3, 0},
		 {3, 3, 3, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}}
	},            
	{	// J型方块
		{{0, 0, 4, 0},
		 {0, 0, 4, 0},
		 {0, 4, 4, 0},
		 {0, 0, 0, 0}},

		{{0, 4, 0, 0},
		 {0, 4, 4, 4},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 4, 4},
		 {0, 0, 4, 0},
		 {0, 0, 4, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 4, 4, 4},
		 {0, 0, 0, 4},
		 {0, 0, 0, 0}}
	},			
	{	// O型方块
		{{0, 0, 0, 0},
		 {0, 5, 5, 0},
		 {0, 5, 5, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 5, 5, 0},
		 {0, 5, 5, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 5, 5, 0},
		 {0, 5, 5, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 5, 5, 0},
		 {0, 5, 5, 0},
		 {0, 0, 0, 0}}
	},		
	{   // S型方块
		{{0, 6, 0, 0},
		 {0, 6, 6, 0},
		 {0, 0, 6, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 6, 6, 0},
		 {6, 6, 0, 0},
		 {0, 0, 0, 0}},

		{{6, 0, 0, 0},
		 {6, 6, 0, 0},
		 {0, 6, 0, 0},
		 {0, 0, 0, 0}},

		{{0, 6, 6, 0},
		 {6, 6, 0, 0},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}}
	},
	{	// Z型方块
		{{0, 0, 7, 0},
		 {0, 7, 7, 0},
		 {0, 7, 0, 0},
		 {0, 0, 0, 0}},

		{{0, 7, 7, 0},
		 {0, 0, 7, 7},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 7},
		 {0, 0, 7, 7},
		 {0, 0, 7, 0},
		 {0, 0, 0, 0}},

		{{0, 0, 0, 0},
		 {0, 7, 7, 0},
		 {0, 0, 7, 7},
		 {0, 0, 0, 0}}
	}		
};

int bricksBound[7][4][4] = 
{
	{{0, 3, 2, 2}, 
	{2, 2, 0, 3}, 
	{0, 3, 2, 2}, 
	{2, 2, 0, 3}},

	{{1, 3, 1, 2}, 
	{2, 3, 1, 3}, 
	{1, 3, 2, 3}, 
	{1, 2, 1, 3}},

	{{1, 2, 0, 2}, 
	{0, 2, 1, 2}, 
	{0, 1, 0, 2}, 
	{0, 2, 0, 1}},

	{{1, 2, 0, 2}, 
	{1, 3, 0, 1}, 
	{2, 3, 0, 2}, 
	{1, 3, 1, 2}},

	{{1, 2, 1, 2}, 
	{1, 2, 1, 2}, 
	{1, 2, 1, 2}, 
	{1, 2, 1, 2}},

	{{1, 2, 0, 2}, 
	{0, 2, 1, 2}, 
	{0, 1, 0, 2}, 
	{0, 2, 0, 1}},

	{{1, 2, 0, 2}, 
	{1, 3, 0, 1}, 
	{2, 3, 0, 2}, 
	{1, 3, 1, 2}}
};

int brickColors[7][3] = 
{
	 {255,0,0}, 
	 {0,255,0}, 
	 {0,0,255}, 
	 {255,255,0}, 
	 {0,255,255}, 
	 {255,0,255}, 
	 {128, 128, 128}
};

int brickType = rand() % 7;
int brickState = rand() % 4;
int nextBrickType =  rand() % 7;
int nextBrickState = rand() % 4;
int brickX = 4;
int brickY = -bricksBound[brickType][brickState][2];
int brickFinalY = 19 - bricksBound[brickType][brickState][3];
int workRegion[20][12] = {0};

int gameState = 0;
int idTimer = 0;
int player = 0;
int mark = 0;
int bestMark = 0;
int layer = 0;
int difficulty = 0;
int timeDelayList[5] = {1000, 800, 500, 300, 150};
int timeDelay = timeDelayList[difficulty];

int loadFlag = 0;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



// Functions
int judgeOverLeft(int currentType, int currentState, int currentX)
{
	int i, j;
	if(currentX + bricksBound[currentType][currentState][0] < 0)
		return 1;
	for(i = 0;i < 4;i++)
		for(j = 0;j < 4;j++)
		{
			if(bricks[currentType][currentState][i][j] > 0  && workRegion[brickY + i][currentX + j] > 0)
				return 1;
		}
	return 0;
}

int judgeOverRight(int currentType, int currentState, int currentX)
{
	int i, j;
	if(currentX + bricksBound[currentType][currentState][1] > 11)
		return 1;
	for(i = 0;i < 4;i++)
		for(j = 3;j >= 0;j--)
		{
			if(bricks[currentType][currentState][i][j] > 0  && workRegion[brickY + i][currentX + j] > 0)
				return 1;
		}
	return 0;
}

int judgeGetBottom(int currentType, int currentState, int currentY)
{
	if(currentY + bricksBound[currentType][currentState][3] >= 19)
		return 1;
	int i, j;
	for(j = 0;j < 4;j++)
		for(i = 3;i >= 0;i--)
		{
			if(bricks[currentType][currentState][i][j] > 0 && currentY + i + 1 <  20 && workRegion[currentY + i + 1][brickX + j] > 0)
				return 1;
		}
	return 0;
}

int judgeGameOver()
{
	int i;
	for(i = 0;i<20;i++)
		if(workRegion[0][i] > 0)
			return 1;
	return 0;
}

void getMark(HWND hWnd)
{
	int i, j, k;
	int full[4] = {0};
	for(j = 0;j < 4;j++)
		for(i = 0;i < 4;i++)
		{
			if(bricks[brickType][brickState][i][j] > 0)
			{
				workRegion[brickY + i][brickX + j]  = bricks[brickType][brickState][i][j];
			}
		}
	for(i = 0;i < 4;i++)
		for(j = 0;j < 12;j++)
			full[i] += workRegion[brickY + i][j] > 0 ? 1: 0; 
	for(i = 0;i<4;i++)
	{
		if(full[i] == 12)
		{
			full[i] = 1;
			workRegion[brickY + i][0]  = -1;
		} 
		else
		{
			full[i] = 0;
		}
	}
	k = 1;
	for(i = 0;i<4;i++)
		k = k<<full[i];
	mark += k / 2 * 100;
	if(mark / 1000  - (mark - k / 2 * 100) / 1000 >= 1)
	{
		difficulty = difficulty > 5 ? difficulty : difficulty + 1;
		timeDelay = timeDelayList[difficulty];
		KillTimer(hWnd, idTimer);
		idTimer = SetTimer(hWnd, 1, timeDelay, NULL);
	}
	for(i = brickY + 3;i >= 0;i--)
		if(workRegion[i][0] == -1)
		{
			for(k = i - 1;k>=0;k--)
				if(workRegion[k][0] != -1)
					break;
			if(k >= 0)
			{
				for(j = 0;j < 12;j++)
					workRegion[i][j] = workRegion[k][j];
				workRegion[k][0] = -1;
			}
			else
			{
				for(j = 0;j < 12;j++)
					workRegion[i][j] = 0;
			}
		}
	return;
}

void getNewBrick()
{
	layer++;
	brickType = nextBrickType;
	brickState = nextBrickState;
	nextBrickType =  rand() % 7;
	nextBrickState = rand() % 4;
	brickX = 4;
	brickY = -bricksBound[brickType][brickState][2];
	return;
}

void getFinalY()
{
	for(brickFinalY = brickY; brickFinalY < 20; brickFinalY ++)
	{
		if(judgeGetBottom(brickType, brickState, brickFinalY) == 1)
			return;
	}
	return;
}

void run(HWND hWnd)
{
	if(judgeGetBottom(brickType, brickState, brickY))
	{
		getMark(hWnd);
		getNewBrick();
	}
	if(judgeGameOver())
	{
		gameState = 2;
		if(mark > bestMark)
		{
			bestMark = mark;
		}
		KillTimer(hWnd, idTimer);
	}
}
void saveGame()
{
	char * fileName = "history.txt";
	FILE * f = fopen("history.txt", "w+");
	fprintf(f, "1 ");
	for(int i = 0;i<20;i++)
		for(int j = 0;j<12;j++)
			fprintf(f, "%d ", workRegion[i][j]);
	fprintf(f, "%d %d %d %d %d", bestMark, mark, layer, difficulty, timeDelay);
	fclose(f);
	return;
}

int loadGame()
{
	FILE * f = fopen("history.txt", "r+");
	fscanf(f, "%d", &loadFlag);
	if(loadFlag > 0)
	{
		for(int i = 0;i<20;i++)
			for(int j = 0;j<12;j++)
				fscanf(f, "%d", &workRegion[i][j]);
		fscanf(f, "%d %d %d %d %d", &bestMark, &mark, &layer, &difficulty, &timeDelay);
		fclose(f);
		FILE * f = fopen("history.txt", "w+");
		fprintf(f, "0 ");
		fclose(f);
	}
	return loadFlag;
}

int makeNewGame()
{
	brickType = rand() % 7;
	brickState = rand() % 4;
	nextBrickType =  rand() % 7;
	nextBrickState = rand() % 4;
	brickX = 4;
	brickY = -bricksBound[brickType][brickState][2];
	brickFinalY = 19 - bricksBound[brickType][brickState][3];
	if(loadGame())
		return 1;
	int i, j;
	for(i = 0;i<20;i++)
		for(j = 0;j<12;j++)
			workRegion[i][j] = 0;


	gameState = 0;
	idTimer = 0;
	player = 0;
	mark = 0;
	layer = 0;
	difficulty = 0;
	timeDelay = timeDelayList[difficulty];
	return 0;
}
void drawRegion(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hbuf;
	hdc = BeginPaint(hWnd, &ps);
	hbuf = CreateCompatibleDC(hdc);
	HBRUSH hBrush;
	HPEN hPen;
	// RECT rt;
	// GetClientRect(hWnd, &rt);

	// draw back
	HBITMAP bmp;
	bmp = (HBITMAP)LoadImage(NULL, _T("back.bmp"), IMAGE_BITMAP, 560, 660, LR_LOADFROMFILE);
	SelectObject(hbuf, bmp);


	// draw right
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	hPen = CreatePen(PS_SOLID, 3, RGB(100, 80, 50));
	SelectObject(hbuf, hBrush);
	SelectObject(hbuf, hPen);
	MoveToEx(hbuf, LEFTREGIONWIDTH+5, 0, NULL);
	LineTo(hbuf, LEFTREGIONWIDTH+5, WINDOWHEIGHT);

	HFONT hFont;
	hFont = CreateFont(0, 0, 0, 0, 800, false, false, false, 
			ANSI_CHARSET, OUT_CHARACTER_PRECIS, 
			CLIP_CHARACTER_PRECIS, PROOF_QUALITY, 
			FF_MODERN, _T("Arial"));
	SelectObject(hdc, hFont);
	SetBkMode(hbuf, TRANSPARENT);
	TextOut(hbuf, LEFTREGIONWIDTH + 20, 40, _T("下一个 :  "), 10);
	TCHAR str[100];
	int len;
	len = wsprintf(str, _T("最佳分数 : %d"), bestMark);
	TextOut(hbuf, LEFTREGIONWIDTH + 20, 300, str, len); 
	len = wsprintf(str, _T("当前分数 : %d"), mark);
	TextOut(hbuf, LEFTREGIONWIDTH + 20, 330, str, len); 
	len = wsprintf(str, _T("当前层数 : %d"), layer);
	TextOut(hbuf, LEFTREGIONWIDTH + 20, 360, str, len); 
	len = wsprintf(str, _T("当前难度: %d"), difficulty);
	TextOut(hbuf, LEFTREGIONWIDTH + 20, 390, str, len); 

	len = wsprintf(str, _T("左:左移 右:右移 下:加速"));
	TextOut(hbuf, LEFTREGIONWIDTH + 10, 450, str, len); 
	len = wsprintf(str, _T("上: 旋转 空格: 落地"));
	TextOut(hbuf, LEFTREGIONWIDTH + 10, 470, str, len); 
	len = wsprintf(str, _T("F1: 重新开始"));
	TextOut(hbuf, LEFTREGIONWIDTH + 10, 490, str, len); 
	len = wsprintf(str, _T("F2: 暂停/继续"));
	TextOut(hbuf, LEFTREGIONWIDTH + 10, 510, str, len); 
	len = wsprintf(str, _T("F3: 存档"));
	TextOut(hbuf, LEFTREGIONWIDTH + 10, 530, str, len); 


	int i, j;
	// draw left
	if(gameState == 0)
	{
		//draw region
		for(i = 0;i<20;i++)
		{
			for(j = 0;j<12;j++)
			{
				int cur = workRegion[i][j];
				if(cur > 0)
				{
					cur--;
					hBrush = CreateSolidBrush(RGB(brickColors[cur][0], brickColors[cur][1], brickColors[cur][2]));
					hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
					SelectObject(hbuf, hBrush);
					SelectObject(hbuf, hPen);
					int x =  j * BRICKSIZE;
					int y =  i * BRICKSIZE;
					Rectangle(hbuf, x, y, x + BRICKSIZE, y+BRICKSIZE);
					DeleteObject(hBrush);
					DeleteObject(hPen);
				}
			}
		}

		getFinalY();
		// draw current 
		for(i = bricksBound[brickType][brickState][2];i <=  bricksBound[brickType][brickState][3];i++)
		{
			for(j = bricksBound[brickType][brickState][0];j <= bricksBound[brickType][brickState][1];j++)
			{
				int cur = bricks[brickType][brickState][i][j];
				if(cur > 0)
				{
					cur--;
					hBrush = CreateSolidBrush(RGB(brickColors[cur][0], brickColors[cur][1], brickColors[cur][2]));
					hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
					SelectObject(hbuf, hBrush);
					SelectObject(hbuf, hPen);
					int x =  (brickX + j) * BRICKSIZE;
					int y =  (brickY + i) * BRICKSIZE;
					Rectangle(hbuf, x, y, x + BRICKSIZE, y+BRICKSIZE);
					DeleteObject(hBrush);
					DeleteObject(hPen);
					hBrush = CreateSolidBrush(RGB(240, 240, 200));
					hPen = CreatePen(PS_SOLID, 3, RGB(220, 220, 200));
					SelectObject(hbuf, hBrush);
					SelectObject(hbuf, hPen);
					x =  (brickX + j) * BRICKSIZE;
					y =  (brickFinalY + i) * BRICKSIZE;
					Rectangle(hbuf, x, y, x + BRICKSIZE, y+BRICKSIZE);
					DeleteObject(hBrush);
					DeleteObject(hPen);
				}
			}
		}
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				int cur = bricks[nextBrickType][nextBrickState][i][j];
				if(cur > 0)
				{
					cur--;
					hBrush = CreateSolidBrush(RGB(brickColors[cur][0], brickColors[cur][1], brickColors[cur][2]));
					hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
					SelectObject(hbuf, hBrush);
					SelectObject(hbuf, hPen);
					int x =  LEFTREGIONWIDTH + 10 + j * BRICKSIZE;
					int y =  i * BRICKSIZE + 80;
					Rectangle(hbuf, x, y, x + BRICKSIZE, y+BRICKSIZE);
					DeleteObject(hBrush);
					DeleteObject(hPen);
				}
			}
		}
	}
	else if(gameState == 2)
	{
		hFont = CreateFont(40, 0, 0, 0, 800, false, false, false, 
				ANSI_CHARSET, OUT_CHARACTER_PRECIS, 
				CLIP_CHARACTER_PRECIS, PROOF_QUALITY, 
				FF_MODERN, _T("Arial"));
		SelectObject(hdc, hFont);
		SetBkMode(hbuf, TRANSPARENT);
		TextOut(hbuf, LEFTREGIONWIDTH + 20, 40, _T("下一个 :  "), 10);
		TCHAR str[100];
		int len;
		len = wsprintf(str, _T("游戏结束! "));
		TextOut(hbuf, 100, 100, str, len); 
		len = wsprintf(str, _T("获得分数 : %d"), mark);
		TextOut(hbuf, 100, 150, str, len); 
		len = wsprintf(str, _T("最大层数: %d"), layer);
		TextOut(hbuf, 100, 200, str, len); 
		if(mark == bestMark)
			len = wsprintf(str, _T("恭喜达到最佳分数记录: %d，太棒了！"), bestMark);
		else
			len = wsprintf(str, _T("历史最佳分数为: %d，继续努力"), bestMark);
		TextOut(hbuf, 100, 250, str, len); 
	}
	BitBlt(hdc, 0, 0, 560, 660, hbuf, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
}

void drawOver()
{
	;

}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_TETRIS);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TETRIS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_TETRIS;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	wcex.hbrBackground = NULL;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

  // hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   hWnd = CreateWindow(szWindowClass, _T("TETRIS"), WS_SYSMENU, WINDOWX, WINDOWY, WINDOWWIDTH, WINDOWHEIGHT, NULL, NULL, hInstance, NULL);



   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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
	int ng = 0;

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CREATE:
			ng = makeNewGame();
			if(ng == 1)
				MessageBox(hWnd, _T("已加载历史记录"), _T("警告"), MB_OK);
			PlaySound (TEXT ("music.wav"), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
			idTimer = SetTimer(hWnd, 1, timeDelay, NULL);
			break;
		case WM_TIMER:
			brickY++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_LEFT:
					if(gameState == 0 && judgeOverLeft(brickType, brickState, brickX - 1) == 0)
					{
						brickX --;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_RIGHT:
					if(gameState == 0 && judgeOverRight(brickType, brickState, brickX + 1) == 0)
					{
						brickX ++;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_UP:
					if(gameState == 0 && (judgeOverLeft(brickType,(brickState + 1) % 4, brickX) == 0) 
						&& (judgeOverRight(brickType,(brickState + 1) % 4, brickX) == 0))
					{
						brickState = (brickState + 1) % 4;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_DOWN:
					if(gameState == 0 && judgeGetBottom(brickType, brickState, brickY) == 0)
					{
						brickY ++;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_SPACE:
					if(gameState == 0)
					{
						brickY = brickFinalY;
						getMark(hWnd);
						getNewBrick();
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_F3:
					if(gameState == 0)
					{
						KillTimer(hWnd, idTimer);
						gameState = 1;
					}
					saveGame();
					MessageBox(hWnd, _T("游戏已保存"), _T("警告"), MB_OK);
					break;
				case VK_F2:
					if(gameState == 0)
					{
						KillTimer(hWnd, idTimer);
						gameState = 1;
						MessageBox(hWnd, _T("已暂停"), _T("警告"), MB_OK);
					}
					else if(gameState == 1)
					{
						idTimer = SetTimer(hWnd, 1, timeDelay, NULL);
						gameState = 0;
					}
					else
					{
						makeNewGame();
						idTimer = SetTimer(hWnd, 1, timeDelay, NULL);
						gameState = 0;
						InvalidateRect(hWnd, NULL, TRUE);
					}
					break;
				case VK_F1:
					KillTimer(hWnd, idTimer);
					makeNewGame();
					idTimer = SetTimer(hWnd, 1, timeDelay, NULL);
					gameState = 0;
					InvalidateRect(hWnd, NULL, TRUE);
				default:
					break;
			}
			break;

		case WM_PAINT:
			// TODO: Add any drawing code here...
			run(hWnd);
			drawRegion(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
