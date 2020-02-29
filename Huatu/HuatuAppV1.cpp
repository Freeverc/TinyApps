#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <locale.h> 
#include <wchar.h>

#define _USE_MATH_DEFINES
#include <math.h>


void jiemian()
{
	// 创建绘图窗口
	initgraph(1000, 600);

	// 画色背景
	setfillcolor(RGB(0, 255, 128));
	solidrectangle(0, 0, 999, 599);

	//添加功能框
	setfillcolor(WHITE);//添加功能框颜色
	setlinecolor(BLACK);
	wchar_t gongNeng[8][8] = { L"画笔",L"直线",L"矩形",L"圆",L"椭圆",L"圆弧",L"扇形", L"清除" };
	for (int i = 0; i < 8; i++)
	{
		fillrectangle(20, 40 * i + 20, 60, 40 * i + 40);
		setbkcolor(WHITE);
		settextcolor(BLUE);
		outtextxy(23, 40 * i + 23, gongNeng[i]);
	}

	//是否填充
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	setbkcolor(WHITE);
	settextcolor(BLUE);
	settextstyle(14, 0, _T("宋体"));
	fillrectangle(80, 20, 140, 40);
	outtextxy(83, 23, L"空心图形");
	fillrectangle(160, 20, 220, 40);
	outtextxy(163, 23, L"填充图形");

	//添加颜色框
	setlinecolor(BLACK);
	COLORREF yanse[16] = { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
		LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW,  WHITE };
	for (int i = 0; i < 16; i++)
	{
		setfillcolor(yanse[i]);
		fillrectangle(240 + 40 * i, 20, 260 + 40 * i, 40);
	}

	//画图窗口
	setfillcolor(WHITE);
	fillrectangle(80, 60, 980, 580);
	HRGN rgn = CreateRectRgn(80, 60, 980, 580);
	// 将该矩形区域设置为裁剪区
	setcliprgn(rgn);
}

int gaibianGongneng(int x, int y)
{
	if ((x < 20) || (x > 60) || (y < 20) || ((y - 20) % 40 > 20))
		return 0;
	else
		return (y - 20) / 40 + 1;
}

int gaibianYanse(int x, int y)
{
	if ((x < 240) || ((x - 240) % 40 > 20) || (y < 20) || (y > 40))
		return 0;
	else
		return (x - 240) / 40 + 1;
}

int gaibianTianchong(int x, int y)
{
	if ((x < 80) || ((x - 80) % 80 > 60) || (y < 20) || (y > 40))
		return 0;
	else
		return (x - 80) / 80 + 1;
}

double getAngle(double x, double y)
{
	double angle = 1;
	if ((x > 0) && (y > 0))
	{
		angle = -atan(y / x);
	}
	else if ((x > 0) && (y < 0))
	{
		angle = -atan(y / x);
	}
	else if ((x < 0) && (y > 0))
	{
		angle = M_PI - atan(y / x);
	}
	else if ((x < 0) && (y < 0))
	{
		angle = M_PI - atan(y / x);
	}
	return angle;

}

int main()
{
	jiemian();

	//COLORREF yanse[9] = { BLACK, RED, BLUE, GREEN, CYAN,YELLOW, MAGENTA, BROWN, WHITE };
	COLORREF yanse[16] = { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW,  WHITE };
	COLORREF dangqianYanse = yanse[0];
	int dangqianGongneng = 0;

	// 主循环
	MOUSEMSG m;
	int xInit, yInit;
	int xGangcai, yGangcai;
	int xYuanxin = 360, yYuanxin = 270;
	int buttonDownFlag = 0;
	int tianchongFlag = 0;
	int Flag;
	int g;

	setlinecolor(dangqianYanse);
	setfillcolor(dangqianYanse);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			buttonDownFlag = 1;

			//改变功能
			g = gaibianGongneng(m.x, m.y);
			if (g != 0)
			{
				dangqianGongneng = g;
			}
			//改变填充
			g = gaibianTianchong(m.x, m.y);
			if (g != 0)
			{
				if (g == 1)
				{
					tianchongFlag = 0;
				}
				else if (g == 2)
				{
					tianchongFlag = 1;
				}
			}
			//改变颜色
			g = gaibianYanse(m.x, m.y);
			if (g != 0)
			{
				dangqianYanse = yanse[g - 1];
				setlinecolor(dangqianYanse);
				setfillcolor(dangqianYanse);
			}

			// 画图
			if ((m.x > 80) && (m.y > 60))
			{
				xInit = m.x;
				yInit = m.y;
				xGangcai = xInit;
				yGangcai = yInit;
			}
		}
		else if (m.uMsg == WM_MOUSEMOVE)
		{
			if (((m.x > 80) && (m.y > 60)) && (buttonDownFlag == 1) && (dangqianGongneng == 1))
			{
				line(xGangcai, yGangcai, m.x, m.y);
				xGangcai = m.x;
				yGangcai = m.y;
			}
		}
		else if (m.uMsg == WM_LBUTTONUP)
		{
			buttonDownFlag = 0;
			if (dangqianGongneng == 8)
			{
				dangqianGongneng = 0;
				setfillcolor(WHITE);
				fillrectangle(80, 60, 980, 580);
				setfillcolor(dangqianYanse);
				continue;
			}
			else
			{
				if ((m.x > 80) && (m.y > 60))
				{
					switch (dangqianGongneng)
					{
					case 1:
					{
						break;
					}
					case 2:
					{
						line(xInit, yInit, m.x, m.y);
						break;
					}
					case 3:
					{
						if (tianchongFlag == 1)
						{
							setfillcolor(dangqianYanse);
							fillrectangle(xInit, yInit, m.x, m.y);
						}
						else
						{
							setlinecolor(dangqianYanse);
							rectangle(xInit, yInit, m.x, m.y);
						}

						break;
					}
					case 4:
					{
						if (tianchongFlag)
							fillcircle(xInit, yInit, sqrt((m.x - xInit) * (m.x - xInit) + (m.y - yInit) * (m.y - yInit)));
						else
							circle(xInit, yInit, sqrt((m.x - xInit) * (m.x - xInit) + (m.y - yInit) * (m.y - yInit)));
						break;
					}
					case 5:
					{
						if (tianchongFlag)
							fillellipse(xInit, yInit, m.x, m.y);
						else
							ellipse(xInit, yInit, m.x, m.y);
						break;
					}
					case 6:
					{
						putpixel(xYuanxin, yYuanxin, BLACK);
						double a, b, x1, x2, y1, y2;
						double startAngle, endAngle;
						x1 = double(xInit - xYuanxin);
						y1 = double(yInit - yYuanxin);
						x2 = double(m.x - xYuanxin);
						y2 = double(m.y - yYuanxin);
						a = sqrt((x1 * x1 * y2 * y2 - x2 * x2 * y1 * y1) / (y2 * y2 - y1 * y1));
						b = sqrt((x2 * x2 * y1 * y1 - x1 * x1 * y2 * y2) / (x2 * x2 - x1 * x1));

						startAngle = getAngle(x1, y1);
						endAngle = getAngle(x2, y2);
						//startAngle = 1;
						//endAngle = 3;
						arc(xYuanxin - a, yYuanxin - b, xYuanxin + a, yYuanxin + b, startAngle, endAngle);
						//arc(xYuanxin - a, yYuanxin - b, xYuanxin + a, yYuanxin + b, 0, 6);
						break;
					}
					case 7:
					{
						putpixel(xYuanxin, yYuanxin, BLACK);
						double a, b, x1, x2, y1, y2;
						double startAngle, endAngle;
						x1 = double(xInit - xYuanxin);
						y1 = double(yInit - yYuanxin);
						x2 = double(m.x - xYuanxin);
						y2 = double(m.y - yYuanxin);
						a = sqrt((x1 * x1 * y2 * y2 - x2 * x2 * y1 * y1) / (y2 * y2 - y1 * y1));
						b = sqrt((x2 * x2 * y1 * y1 - x1 * x1 * y2 * y2) / (x2 * x2 - x1 * x1));

						startAngle = getAngle(x1, y1);
						endAngle = getAngle(x2, y2);
						//startAngle = 1;
						//endAngle = 3;
						if (tianchongFlag == 1)
							fillpie(xYuanxin - a, yYuanxin - b, xYuanxin + a, yYuanxin + b, startAngle, endAngle);
						else
							pie(xYuanxin - a, yYuanxin - b, xYuanxin + a, yYuanxin + b, startAngle, endAngle);
						//arc(xYuanxin - a, yYuanxin - b, xYuanxin + a, yYuanxin + b, 0, 6);
						break;
					}
					default:
						break;
					}
				}
			}
		}
		else if (m.uMsg == WM_RBUTTONDOWN)
		{
			if (((m.x > 80) && (m.y > 60)) && ((dangqianGongneng == 6) || (dangqianGongneng == 7)))
			{
				xYuanxin = m.x;
				yYuanxin = m.y;
				putpixel(xYuanxin, yYuanxin, BLACK);
			}
		}
	}
	// 按任意键退出
	//_getch();
	closegraph();
}
