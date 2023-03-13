#include "Shape.h"

int* Shape::x = NULL;
int* Shape::y = NULL;
int Shape::mino = 0;
int Shape::arraylen = 0;

// �R���X�g���N�^
Shape::Shape()
{
	int i;

	array = new int [arraylen];
	for(i = 0; i < arraylen; i++)
		array[i] = 0;
}

// �f�X�g���N�^
Shape::~Shape()
{
	delete [] array;
}

// ���ׂẮ����אڂ��Ă��邩�ǂ������`�F�b�N����
// �߂�l : �אڂ��Ă�����true�C�אڂ��Ă��Ȃ�������false
bool Shape::iscorrect()
{
	int i;

	next(0, 0);
	for(i = 0; (i < arraylen) && (array[i] != 1); i++);
	if(i == arraylen)
		return true;
	else
		return false;
}

// (ax,ay)�̗אځ��ɂ܂��`�F�b�N���Ă��Ȃ�1����������2�ɂ���
// ax : �����Ώۂ̂����W
// ay : �����Ώۂ̂����W
void Shape::next(int ax, int ay)
{
	next2(ax, ay+1);
	next2(ax, ay-1);
	next2(ax+1, ay);
	next2(ax-1, ay);
}

// (ax,ay)��1��������2�ɂ��čċA�ďo��
// ax : �����Ώۂ̂����W
// ay : �����Ώۂ̂����W
void Shape::next2(int ax, int ay)
{
	int n;

	n = (mino-ax-1) * (mino-ax) + ay;
	if((ax >= 0) && (ax < mino) && (ay > ax-mino) && (ay < mino-ax)
		&& (n < arraylen) && (array[n] == 1)) {
		array[n] = 2;
		next(ax, ay);
	}
}

// array��a�������z�񂩂ǂ������`�F�b�N
// a : ��r�Ώۂ̔z��
// �߂�l : �����Ƃ�true�C�Ⴄ�Ƃ�false
bool Shape::issame(int* a)
{
	int i;

	for(i = 0; (i < arraylen) && ((!array[i] && !a[i]) || (array[i] && a[i])); i++);
	if(i == arraylen)
		return true;
	else
		return false;
}