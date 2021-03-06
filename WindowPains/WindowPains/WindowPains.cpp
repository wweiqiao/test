                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // WindowPains.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "string"
#include "iostream"
using namespace std;

const int n = 4;
int screen[4][4];			//屏幕显示的内容
string cover[4][4];			//能够覆盖（i，j）位置的窗口的集合
bool exist[10];				//某个窗口是否在屏幕上出现
int id[10];					//入度
bool g[10][10];				//邻接表
int t;
string s;
void calc()					//统计覆盖(i,j)位置的窗口的集合
{
	int i, j, k;
	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < n; j++)
		{
			cover[i][j].erase();
		}
	}

	for ( k = 1; k <= 9; k++)
	{
		i = (k - 1) / 3;
		j = (k - 1) % 3;
		cover[i][j] += char(k + '0');
		cover[i][j+1] += char(k + '0');
		cover[i+1][j] += char(k + '0');
		cover[i+1][j+1] += char(k + '0');

	}
}

//读入屏幕上的数据
void init()
{
	int i, j, k;
	memset(exist, 0, sizeof(exist));
	memset(id, 0, sizeof(id));
	memset(g, 0, sizeof(g));
	t = 0;
	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < n; j++)
		{
			cin >> k;
			screen[i][j] = k;
			if (!exist[k]) t++;
			exist[k] = true;
		}
	}
}

void build()					//根据屏幕上的数据构建有向图，类似于存储表
{
	int i, j, p;
	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < n; j++)
		{
			for ( p = 0; p < cover[i][j].length(); p++)
			{
				if ((!g[screen[i][j]][cover[i][j][p] - '0']) && (screen[i][j] != cover[i][j][p] - '0'))
				{
					g[screen[i][j]][cover[i][j][p] - '0'] = true;
					id[cover[i][j][p] - '0']++;			//入度加1
				}
			}
		}
	}
}

bool check()		//判断是否存在有向图
{
	int i, j, k;
	for ( k = 0; k < t; k++)
	{
		i = 1;
		while (!exist[i] || (i <= 9 && id[i] > 0))
			i++;
		if (i > 9)
			return false;
		exist[i] = false;
		for ( j = 0; j <= 9; j++)
		{
			if (exist[j] && g[i][j])
				id[j]--;
		}
	}
	return true;
}

int main()
{
	calc();
	while (cin >> s)
	{
		if (s == "ENDOFINPUT")break;
		init();
		build();
		if (check())	cout << "THESE WINDOWS ARE CLEAN.\n";
		else cout << "THESE WINDOWS ARE BROKEN.\n";
		cin >> s;
	}
    return 0;
}

