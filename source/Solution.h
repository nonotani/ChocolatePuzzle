#pragma once

#include "Set.h"

class Solution  
{
public:
	static int row;
	static int col;

	Solution(int** aarray);
	virtual ~Solution();
	bool add(int** aarray);

	int** array;
	Solution* next;

private:
	bool same(int** a, int** b);
};
