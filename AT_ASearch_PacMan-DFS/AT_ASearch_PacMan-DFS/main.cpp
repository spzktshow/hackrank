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
	char tile = getTile(ri, ci, grid);
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

/******根据索引获取ri******/
int getRi(int index, int c)
{
	return (int)index / c;
}

/*******根据缩影获取ci********/
int getCi(int index, int c)
{
	return  index % c;
}

int calculateH(int startRi, int startCi, int endRi, int endCi)
{
	return (abs(endRi - startRi) + abs(endCi - startCi));
}

/********计算从结束的索引到开始的索引一共有几步*********/
int calculateTotalStep(vector <int> fatherList, int endIndex)
{
	int count = 0;
	int index = endIndex;
	while(fatherList[index] != -1)
	{
		count ++;
		index = fatherList[index];
	}
	return count;
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
	int index = 0;
	for (index; index < total; index ++)
	{
		openList.push_back(false);
		closeList.push_back(false);
		fList.push_back(0);
		gList.push_back(0);
		hList.push_back(0);
		fatherList.push_back(-1);
	}
	//search
	int search_r, search_c, check_r, check_c, f, g, h;
	search_r = pacman_r;
	search_c = pacman_c;
	index = getIndex(search_r, search_c, c);

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
				if (openList[checkIndex] == true || closeList[checkIndex] == true)
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
			check_r = search_r;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[checkIndex] == true || closeList[checkIndex] == true)
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
			check_c = search_c;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[checkIndex] == true || closeList[checkIndex] == true)
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
			check_r = search_r;
			isAllowValue = isAllow(check_r, check_c, grid);
			if (isAllowValue)
			{
				checkIndex = getIndex(check_r, check_c, c);
				g = gList[index] + 1;
				h = calculateH(check_r, check_c, food_r, food_c);
				f = g + h;
				if (openList[checkIndex] == true || closeList[checkIndex] == true)
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
		for (int i = 0; i < openList.size(); i ++)
		{
			if (openList.at(i) == true)
			{
				if (f == -1 || fList.at(i) < f)
				{
					index = i;
					f = fList.at(i);
				}
			}
		}
		search_r = getRi(index, c);
		search_c = getCi(index, c);
	}
	 /***获取列表***/
	index = getIndex(food_r, food_c, c);
	int totalStep = calculateTotalStep(fatherList, index);
	std::cout << totalStep << std::endl;
	/***用于反转的fatherList****/
	vector <int> convertFatherList;
	convertFatherList.push_back(index);
	int fatherIndex = fatherList[index];
	while(fatherIndex != -1)
	{
		convertFatherList.push_back(fatherIndex);
		fatherIndex = fatherList[fatherIndex];
	}
	int j = convertFatherList.size() - 1;
	for (j; j >= 0; j --)
	{
		index = convertFatherList.at(j);
		std::cout << getRi(index, c) << " " << getCi(index, c) << endl;
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

	int t;
	cin >> t;
	return 0;
}