#include "Piece.h"

// コンストラクタ
Piece::Piece()
{
	array = new Shape* [8];
	for(int i = 0; i < 8; i++)
		array[i] = NULL;
}

// デストラクタ
Piece::~Piece()
{
	delete [] array;
}
