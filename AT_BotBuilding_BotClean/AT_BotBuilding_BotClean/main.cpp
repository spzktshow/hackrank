#include<iostream>
#include<vector>
#include<string>
#include<math.h>
using namespace std;

const char cleanCell = '-';
const char dirtyCell = 'd';
const char bot = 'b';

const string RIGHT = "RIGHT";
const string LEFT = "LEFT";
const string UP = "UP";
const string DOWN = "DOWN";

/**convert board to list*/
vector <char> convertList(vector <string> board)
{
	vector <char> list;
	int n = board.size();
	for (int i = 0; i < n; i ++)
	{
		string s = board.at(i);
		for (int j = 0; j < n; j ++)
		{
			char c = s.at(j);
			list.push_back(c);
		}
	}
	return list;
}

/**convert list to board*/
vector <string> convertBoard(vector <char> list)
{
	vector <string> board;
	int n = list.size();
	int len = (int) sqrt(n);
	string s;
	for (int i = 0; i < n; i ++)
	{
		char c = list.at(i);
		if (i % len == 0)
		{
			s = c;
		}
		else
		{
			s.push_back(c);
		}
		if (i % len == len - 1)
		{
			board.push_back(s);
		}
	}
	return board;
}

/**check next step direct if false is left , then true is right*/
bool checkRowDirect(int posr)
{
	if (posr % 2 == 0) return true;
	return false;
}

/**check has dirty cell?*/
int checkLast(vector <char> list)
{
	int n = list.size();
	for (int i = 0; i < n; i ++)
	{
		char c = list.at(i);
		if (c == dirtyCell)
		{
			return i;
		}
	}
	return -1;
}

/**check matrixIndex is Dirty?*/
bool checkMatrixIndexDirty(int index, vector <char> list)
{
	char c = list.at(index);
	if (c == dirtyCell)
	{
		return true;
	}
	return false;
}

/**if matrixIndex is Dirty then clean it*/
vector <char> cleanMatrixIndex(vector <int> matrixIndex, vector <char> list)
{
	int len = (int) sqrt(list.size());
	int index = matrixIndex[0] * len + matrixIndex[1];
	if (checkMatrixIndexDirty(index, list))
	{
		list[index] = bot;
	}
	return list;
}

/**(row, col)*/
vector <int> convertIndexToMatrixIndex(int index, int len)
{
	vector <int> matrixIndex;
	matrixIndex.push_back((int) (index / len));
	matrixIndex.push_back((int) (index % len));
	return matrixIndex;
}

/* Head ends here */
void next_move(int posr, int posc, vector <string> board) {
	//add logic here
	vector <char> list = convertList(board);
	vector <int> currentP;
	currentP.push_back(posr);
	currentP.push_back(posc);
	list = cleanMatrixIndex(currentP, list);
	int index = checkLast(list);
	if (index == -1) return;
	//matrix
	vector <int> dirtyMatrixIndex = convertIndexToMatrixIndex(index, board.size());
	int rowIndexGap = dirtyMatrixIndex.at(0) - posr;
	int colIndexGap = dirtyMatrixIndex.at(1) - posc;
	if (colIndexGap > 0)
	{
		cout << RIGHT << endl;
		currentP[0] = posr;
		currentP[1] = posc + 1;
		list = cleanMatrixIndex(currentP, list);
	}
	else if (colIndexGap < 0)
	{
		cout << LEFT << endl;
		currentP[0] = posr;
		currentP[1] = posc - 1;
		list = cleanMatrixIndex(currentP, list);
	}
	else
	{
		if (rowIndexGap > 0)
		{
			cout << DOWN << endl;
			currentP[0] = posr + 1;
			currentP[1] = posc;
			list = cleanMatrixIndex(currentP, list);
		}
		else if (rowIndexGap < 0)
		{
			cout << UP << endl;
			currentP[0] = posr - 1;
			currentP[1] = posc;
			list = cleanMatrixIndex(currentP, list);
		}
		else
		{
			return;
		}
	}
	board = convertBoard(list);
	next_move(currentP[0], currentP[1], board);
}

/* Tail starts here */
int main(void) {
	int pos[2];
	vector <string> board;
	cin>>pos[0]>>pos[1];
	for(int i=0;i<5;i++) {
		string s;
		cin >> s;
		board.push_back(s);
	}
	next_move(pos[0], pos[1], board);
	system("pause");
	return 0;
}