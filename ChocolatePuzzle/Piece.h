#pragma once

#include "Shape.h"

class Piece  
{
public:
	Piece();
	virtual ~Piece();

	Shape** array;
};
