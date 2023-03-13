#pragma once

#include "Piece.h"

class Set  
{
public:
	Set(int amino);
	virtual ~Set();
	int makeShape(Shape** candidate, int max, int num, int next);

	int mino;
	int pnum;
	Piece** array;

private:
	void turn(int* a, int* b);
	void leftrotate(int* a, int* b);
};
