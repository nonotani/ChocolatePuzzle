#include "Piece.h"

// �R���X�g���N�^
Piece::Piece()
{
	array = new Shape* [8];
	for(int i = 0; i < 8; i++)
		array[i] = NULL;
}

// �f�X�g���N�^
Piece::~Piece()
{
	delete [] array;
}
