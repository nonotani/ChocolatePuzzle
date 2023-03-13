#include "Solution.h"

int Solution::row = 0;
int Solution::col = 0;

// コンストラクタ
Solution::Solution(int** aarray)
{
	array = new int* [row];
	for(int i = 0; i < row; i++) {
		array[i] = new int [col];
		for(int j = 0; j < col; j++)
			array[i][j] = aarray[i][j];
	}
	next = NULL;
}

// デストラクタ
Solution::~Solution()
{
	for(int i = 0; i < row; i++)
		delete [] array[i];
	delete [] array;
	if(next)
		delete next;
}

// 見つかった配列が既にある配列と同じでなければ加える
// aarray : 追加候補の配列
// 戻り値 : 追加できたらtrue，できなかったらfalse
bool Solution::add(int** aarray)
{
	Solution* p = this;
	Solution* pp = this;

	do {
		if(same(p->array, aarray))
			break;
		pp = p;
		p = p->next;
	} while(p);
	if(p) {
		return false;
	} else {
		pp->next = new Solution(aarray);
		return true;
	}
}

// ２つの配列を180度回転，左右裏返し，左右裏返し＆180度回転して同じかどうかを調べる
// a : 比較する配列
// b : 比較する配列
// 戻り値 : 同じになったらtrue，ならなかったらfalse
bool Solution::same(int** a, int** b)
{
	int i, j;

	// 180度回転
	for(i = 0; i < row; i++) {
		for(j = 0; (j < col) && (a[i][j] == b[row-1-i][col-1-j]); j++);
		if(j != col)
			break;
	}
	if(i == row)
		return true;
	// 左右裏返し
	for(i = 0; i < row; i++) {
		for(j = 0; (j < col) && (a[i][j] == b[i][col-1-j]); j++);
		if(j != col)
			break;
	}
	if(i == row)
		return true;
	// 左右裏返し＆180度回転
	for(i = 0; i < row; i++) {
		for(j = 0; (j < col) && (a[i][j] == b[row-1-i][j]); j++);
		if(j != col)
			break;
	}
	if(i == row)
		return true;
	else
		return false;
}
