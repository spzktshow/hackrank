#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

const char road = '-';
const char barr = '%';

/********获取tile*********/
char getTile(int ri, int ci, vector <string> grid)
{
	string str = grid.at(ri);
	char tile = str.at(ci);
	return tile;
}

/*********根据索引,已经grid数据,列表中的index********/
int getIndex(int ri, int ci, int c)
{
	return ri * c + ci;
}

bool isAllow(int ri, int ci, vector <string> grid)
{
	char tile = getTile(ri, ri, grid);
	if (tile == road) return true;
	return false;
}
/***检查是否越界**/
bool isInternal(int ri, int ci, int r, int c)
{
	if (ri < r && ci < c && ri >= 0 && ci >- 0)
	{
		return true;
	}
	return false;
}

int calculateH(int startRi, int startCi, int endRi, int endCi)
{
	return (abs(endRi - startRi) + abs(endCi - startCi));
}

/****r,c grid的row和col****/
void dfs( int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid)
{
	vector <bool> openList;
	vector <bool> closeList;
	vector <int> fList;
	vector <int> gList;
	vector <int> hList;
	vector <int> fatherList;
	/***总共的tile数***/
	const unsigned int total = r * c;
	/**初始化openList closeList**/
	int index;
	for (index = 0; index < total; index ++)
	{
		openList[index] = false;
		closeList[index] = false;
		fList[index] = 0;
		gList[index] = 0;
		hList[index] = 0;
		fatherList[index] = -1;
	}
	//search
	int search_r, search_c, check_r, check_c, f, g, h;
	search_r = pacman_r;
	search_c = pacman_c;
	int index = getIndex(search_r, search_c, c);
	gList[index] = 0;
	

	bool isAllowValue;
	int checkIndex;
	while(search_r != food_r || search_c != food_c)
	{
		/***遍历点的四周****/
		/*********检查4个方向,分别是top, right, bottom, left*********/
		check_r = search_r - 1;
		if (check_r >= 0)//top
		{
			check_c = search_c;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[index] == true || closeList[index] == true)
				{
					if (fList[checkIndex] > f)
					{
						gList[checkIndex] = g;
						hList[checkIndex] = h;
						fList[checkIndex] = g + h;
						fatherList[checkIndex] = index;
					}
				}
				else
				{
					gList[checkIndex] = g;
					hList[checkIndex] = h;
					fList[checkIndex] = g + h;
					fatherList[checkIndex] = index;

					openList[checkIndex] = true;
				}
			}
		}
		check_c = search_c + 1;
		if (check_c < c)//right
		{
			check_r = search_r = r;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[index] == true || closeList[index] == true)
				{
					if (fList[checkIndex] > f)
					{
						gList[checkIndex] = g;
						hList[checkIndex] = h;
						fList[checkIndex] = g + h;
						fatherList[checkIndex] = index;
					}
				}
				else
				{
					gList[checkIndex] = g;
					hList[checkIndex] = h;
					fList[checkIndex] = g + h;
					fatherList[checkIndex] = index;

					openList[checkIndex] = true;
				}
			}
		}
		check_r = search_r + 1;
		if (check_r < r)//bottom
		{
			check_c = c;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[index] == true || closeList[index] == true)
				{
					if (fList[checkIndex] > f)
					{
						gList[checkIndex] = g;
						hList[checkIndex] = h;
						fList[checkIndex] = g + h;
						fatherList[checkIndex] = index;
					}
				}
				else
				{
					gList[checkIndex] = g;
					hList[checkIndex] = h;
					fList[checkIndex] = g + h;
					fatherList[checkIndex] = index;

					openList[checkIndex] = true;
				}
			}
		}
		check_c = search_c - 1;
		if (check_c >= 0)//left
		{
			check_r = r;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[index] == true || closeList[index] == true)
				{
					if (fList[checkIndex] > f)
					{
						gList[checkIndex] = g;
						hList[checkIndex] = h;
						fList[checkIndex] = g + h;
						fatherList[checkIndex] = index;
					}
				}
				else
				{
					gList[checkIndex] = g;
					hList[checkIndex] = h;
					fList[checkIndex] = g + h;
					fatherList[checkIndex] = index;

					openList[checkIndex] = true;
				}
			}
		}
		closeList[index] = true;
		if (openList.size() <= 0)
		{
			return;
		}
		openList[index] = false;
		f = -1;
		for (int i = 0; i < fList.size(); i ++)
		{
			if (f == -1 || fList.at(i) < f)
			{
				index = i;
				f = fList.at(i);
			}
		}
	}

}

int main(void)
{
	int r,c, pacman_r, pacman_c, food_r, food_c;

	cin >> pacman_r >> pacman_c;
	cin >> food_r >> food_c;
	cin >> r >> c;

	vector <string> grid;

	for(int i=0; i<r; i++) {
		string s; cin >> s;
		grid.push_back(s);
	}

	dfs( r, c, pacman_r, pacman_c, food_r, food_c, grid);

	int endInt;
	cin >> endInt;
	return 0;
}