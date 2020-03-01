#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

constexpr auto MAX100 = 100;
constexpr auto MAX20 = 20;

int main()
{
	int a[5][4];
	int mode = 0, zongBushu = 10, bushu = 0;
	clock_t start, finish;
	double duration;
	//初始化界面
	initgraph(300, 540);
	int caozuoAnjian[4] = {100, 102, 106, 107};
	int gongnengAnjian[4] = {117, 105, 111, 113};
	for (int i = 0; i < 5; i++)
	{
		int heiIndex = rand() % 4;
		for (int j = 0; j < 4; j++)
		{
			if (j == heiIndex)
			{
				a[i][j] = 1;
				setfillcolor(BLACK);
			}
			else
			{
				a[i][j] = 0;
				setfillcolor(WHITE);
			}
			fillrectangle(j * 75, i * 100, (j + 1) * 75, (i + 1) * 100);
			printf("%d ", a[i][j]);
		}
	}
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 500, 299, 519);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	settextstyle(16, 0, _T("宋体"));
	TCHAR anjiantishi[] = _T("    d        f        j        k");
	outtextxy(0, 502, anjiantishi);

	setfillcolor(CYAN);
	solidrectangle(0, 520, 299, 539);
	settextcolor(BLACK);
	setbkcolor(CYAN);
	settextstyle(16, 0, _T("宋体"));
	TCHAR moshitishi[] = _T("模式：u:无尽 i:20格 o:100格 q:退出");
	outtextxy(0, 522, moshitishi);

	int ch;
	int gameState = 0;
	int find = 0;
	int id = 0;
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			//退出程序
			if (ch == 113)
			{
				closegraph();
				return 0;
			}
			//游戏成功或者失败状态
			else if ((gameState == 2) || (gameState == 3))
			{
				if (ch == 32)
				{				
					gameState = 0;
					duration = 0;
					bushu = 0;
					for (int i = 0; i < 5; i++)
					{
						int heiIndex = rand() % 4;
						for (int j = 0; j < 4; j++)
						{
							if (j == heiIndex)
							{
								a[i][j] = 1;
								setfillcolor(BLACK);
							}
							else
							{
								a[i][j] = 0;
								setfillcolor(WHITE);
							}
							fillrectangle(j * 75, i * 100, (j + 1) * 75, (i + 1) * 100);
							printf("%d ", a[i][j]);
						}
					}
				}
			}
			//游戏未开始或者进行状态
			else
			{	
				find = 0;
				id = 0;
				//游戏未开始状态
				if (gameState == 0)
				{
					//开始计时
					duration = 0;
					start = clock();
					//检查功能按键
					for (id = 0; id < 3; id++)
					{
						if (ch == gongnengAnjian[id])
						{
							find = 2;
							mode = id;
							if (mode == 1)
							{
								zongBushu = MAX20;
							}
							else if (mode == 2)
							{
								zongBushu = MAX100;
							}
							break;
						}
					}
				}

				//检查操作按键
				for (id = 0; id < 4; id++)
				{
					if (ch == caozuoAnjian[id])
					{
						find = 1;
						break;
					}
				}

				//按了操作按键并且按对了
				if((find == 1) && (a[4][id] == 1))
				{
					if (gameState == 0)
					{
						gameState = 1;
					}
					bushu++;
					//不是无尽模式，并且步数够了
					if ((mode != 0) &&(bushu >= zongBushu))
					{
						// 赢了
						gameState = 2;
						finish = clock();
						duration = (double)(finish - start) / CLOCKS_PER_SEC;
						setfillcolor(RED);
						fillrectangle(0, 0, 299, 499);
						TCHAR shijian[100];
						_stprintf_s(shijian, _T("You used %lf seconds"), duration);
						settextcolor(YELLOW);
						setbkcolor(RED);
						settextstyle(40, 0, _T("黑体"));
						TCHAR jieguo[] = _T("You win!");
						outtextxy(70, 100, jieguo);
						settextstyle(20, 0, _T("黑体"));
						outtextxy(30, 300, shijian);
						continue;
					}
					//无尽模式，或者步数不够
					else
					{
						//平移
						for (int i = 4; i > 0; i--)
						{
							for (int j = 0; j < 4; j++)
							{
								a[i][j] = a[i - 1][j];
							}
						}
						//填充第一行
						int heiIndex = rand() % 4;
						for (int j = 0; j < 4; j++)
						{
							if (j == heiIndex)
								a[0][j] = 1;
							else
								a[0][j] = 0;
						}
						//画新界面
						for (int i = 0; i < 5; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (a[i][j] == 1)
								{
									setfillcolor(BLACK);
								}
								else
								{
									setfillcolor(WHITE);
								}
								fillrectangle(j * 75, i * 100, (j + 1) * 75, (i + 1) * 100);
								printf("%d ", a[i][j]);
							}
						}
					}
				}
				
				//按了功能按键
				else if (find == 2)
				{
					continue;
				}
				//没有按功能按键和操作按键，或者按错了操作按键
				else
				{
					//输了
					gameState = 3;
					finish = clock();
					duration = (double)(finish - start) / CLOCKS_PER_SEC;
					setfillcolor(BLUE);
					fillrectangle(0, 0, 299, 499);
					TCHAR shijian[100];
					_stprintf_s(shijian, _T("You used %lf seconds"), duration);
					settextcolor(YELLOW);
					setbkcolor(BLUE);
					settextstyle(40, 0, _T("黑体"));
					TCHAR jieguo[] = _T("You fail!");
					outtextxy(70, 100, jieguo);
					settextstyle(20, 0, _T("黑体"));
					outtextxy(30, 300, shijian);
				}

			}
		}
	}
	closegraph();
	return 0;
}


