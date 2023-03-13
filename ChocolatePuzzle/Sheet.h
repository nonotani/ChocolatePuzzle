#pragma once

#include "Solution.h"

class Sheet  
{
public:
	Sheet(int row, int col);
	virtual ~Sheet();
	void solve(Set* a);
	void solve2(int n);

	int row;
	int col;
	int sol_n;
	int** array;
	Solution* sol;

private:
	bool put_piece(int n);
	void del_piece(int n);
	bool next_piece(int n);

	Set* set_p;
	int* piece_a;
	int* shape_a;
	FILE* outFile;
};
