#pragma once

#include "myfunc.h"

class Shape  
{
public:
	Shape();
	virtual ~Shape();
	bool iscorrect();
	void next(int ax, int ay);
	void next2(int ax, int ay);
	bool issame(int* a);

	static int* x;
	static int* y;
	static int mino;
	static int arraylen;
	int* array;
};
