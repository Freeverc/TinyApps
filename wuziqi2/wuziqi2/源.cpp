
#include <graphics.h>
#include <iostream>
#include <graphics.h>

const int WIDTH = 600;
const int SHUMI = 20;
const int HANGSHU = WIDTH / SHUMI;

//ª≠ΩÁ√Ê
void jiemian(int  qipan[HANGSHU][HANGSHU])
{
	initgraph(WIDTH, WIDTH);
	setfillcolor(BROWN);
	fillrectangle(0, 0, WIDTH - 1, WIDTH - 1);

	for (int i = 0; i < WIDTH; i += SHUMI)
	{
		for (int j = 0; j < WIDTH; j += SHUMI)
		{
			setlinecolor(BLACK);
			line(0, j, WIDTH, j);
			line(i, 0, i, WIDTH);

		}
	}
	for (int i = 0; i < HANGSHU; i++)
	{
		for (int j = 0; j < HANGSHU; j++)
		{
			qipan[i][j] = 0;
		}
	}
	return;
}

int judge(int  qipan[HANGSHU][HANGSHU], int dangqianH, int dangqianL, int heiBai)
{
	int result = 0;
	int label[3][3] = { 0 };
	int zhengfu[3] = { 1, -1, 0 };
	int zoudaoH, zoudaoL;
	int dangqian, zoudao;
	dangqian = qipan[dangqianH][dangqianL];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i == 2) && (j == 2))
			{
				return result;
			}
			else
			{
				for (int k = 1; k < 100; k++)
				{
					zoudaoH = dangqianH + k * zhengfu[i];
					zoudaoL = dangqianL + k * zhengfu[j];
					zoudao = qipan[zoudaoH][zoudaoL];
					if ((zoudaoH < 0) || (zoudaoH > HANGSHU - 1) || (zoudaoL < 0) || (zoudaoL > HANGSHU - 1)
						|| (qipan[zoudaoH][zoudaoL] != qipan[dangqianH][dangqianL]))
					{
						break;
					}
					else
					{
						label[i][j] ++;
					}
				}
				int aa;
				aa = 1;

			}
		}
	}
	int t = 0;
	t = 4;
	if ((label[2][0] + label[2][1] > 3) || (label[0][2] + label[1][2] > 3)
		|| (label[0][0] + label[1][1] > 3) || (label[1][0] + label[0][1] > 3))
	{
		result = qipan[dangqianH][dangqianL];
		t = heiBai;
	}
	int b = 0;
	b++;
	return result;
}

int main()
{
	MOUSEMSG m;
	int heiBai = 1, gameState = 0;
	int qipan[HANGSHU][HANGSHU];
	int dangqianH, dangqianL;
	jiemian(qipan);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			dangqianH = m.y / SHUMI;
			dangqianL = m.x / SHUMI;
			if (m.y - dangqianH * SHUMI > 10)
			{
				dangqianH++;
			}
			if (m.x - dangqianL * SHUMI > 10)
			{
				dangqianL++;
			}
			if (qipan[dangqianH][dangqianL] == 0)
			{
				qipan[dangqianH][dangqianL] = heiBai;
				if (heiBai == 1)
				{
					setfillcolor(BLACK);
					heiBai = 2;
				}
				else if (heiBai == 2)
				{
					setfillcolor(WHITE);
					heiBai = 1;
				}
				fillcircle(dangqianL * SHUMI, dangqianH * SHUMI, 5);

				int result = 0;
				result = judge(qipan, dangqianH, dangqianL, heiBai);
				if (result == 1)
				{
					setfillcolor(BLACK);
					fillrectangle(0, 0, WIDTH - 1, WIDTH - 1);
				}
				else if (result == 2)
				{
					setfillcolor(WHITE);
					fillrectangle(0, 0, WIDTH - 1, WIDTH - 1);
				}

			}
		}

		else if (m.uMsg == WM_LBUTTONUP)
		{


		}
	}
	return 0;
}

