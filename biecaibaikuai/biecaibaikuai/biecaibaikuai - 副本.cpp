#include <stdio.h>
#include <iostream>
#include<graphics.h>
#include <conio.h>
#include<stdlib.h> 
#include <string.h>
#include <locale.h> 

int main()
{
	int a[5][4];
	//初始化界面
	initgraph(300, 500);
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

	MOUSEMSG m;
	int xInit, yInit;
	COLORREF r;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			xInit = m.x;
			yInit = m.y;
			r = getpixel(xInit, yInit);
			if (r == BLUE)
			{
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
			else if (yInit > 400)
			{
				
				if (r == BLACK)
				{
					for (int i = 4; i  > 0; i--)
					{
						for (int j = 0; j < 4; j++)
						{
							a[i][j] = a[i-1][j];
						}
					}
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
				else
				{
					setfillcolor(BLUE);
					fillrectangle(0, 0, 299, 499);
				}
			}
			
			else
			{
				setfillcolor(BLUE);
				fillrectangle(0, 0, 299, 499);
			}
		}
	}
	closegraph();
	return 0;
}


