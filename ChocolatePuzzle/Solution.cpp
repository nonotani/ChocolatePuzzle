#include "Solution.h"

int Solution::row = 0;
int Solution::col = 0;

// �R���X�g���N�^
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

// �f�X�g���N�^
Solution::~Solution()
{
	for(int i = 0; i < row; i++)
		delete [] array[i];
	delete [] array;
	if(next)
		delete next;
}

// ���������z�񂪊��ɂ���z��Ɠ����łȂ���Ή�����
// aarray : �ǉ����̔z��
// �߂�l : �ǉ��ł�����true�C�ł��Ȃ�������false
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

// �Q�̔z���180�x��]�C���E���Ԃ��C���E���Ԃ���180�x��]���ē������ǂ����𒲂ׂ�
// a : ��r����z��
// b : ��r����z��
// �߂�l : �����ɂȂ�����true�C�Ȃ�Ȃ�������false
bool Solution::same(int** a, int** b)
{
	int i, j;

	// 180�x��]
	for(i = 0; i < row; i++) {
		for(j = 0; (j < col) && (a[i][j] == b[row-1-i][col-1-j]); j++);
		if(j != col)
			break;
	}
	if(i == row)
		return true;
	// ���E���Ԃ�
	for(i = 0; i < row; i++) {
		for(j = 0; (j < col) && (a[i][j] == b[i][col-1-j]); j++);
		if(j != col)
			break;
	}
	if(i == row)
		return true;
	// ���E���Ԃ���180�x��]
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
