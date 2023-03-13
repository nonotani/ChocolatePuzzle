#include "Set.h"

// �R���X�g���N�^
// amino : �P�s�[�X�́��̌�
Set::Set(int amino)
{
	int i, j, k, l, cannum;
	Shape** candidate;
	int** changearray;

	mino = amino;
	// shape�N���X��static�ϐ���ݒ�
	Shape::mino = mino;
	Shape::arraylen = mino * mino - mino;
	Shape::x = new int [Shape::arraylen];
	Shape::y = new int [Shape::arraylen];
	for(k = 0, i = mino-1; i > 0; i--) {
		for(j = i-mino+1; j < -i+mino; j++, k++) {
			Shape::x[k] = i;
			Shape::y[k] = j;
		}
	}
	for(j = -mino+1; j < 0; j++, k++) {
		Shape::x[k] = 0;
		Shape::y[k] = j;
	}

	// �s�[�X�̌`������Ă݂�
	cannum = combination(Shape::arraylen, mino-1);
	candidate = new Shape* [cannum];
	for(i = 0; i < cannum; i++)
		candidate[i] = new Shape();
	makeShape(candidate, candidate[0]->arraylen, mino-1, 0);

	// �אڂ��Ă��Ȃ���������s�[�X���폜
	for(i = 0; i < cannum; i++) {
		if(!candidate[i]->iscorrect()) {
			delete candidate[i];
			candidate[i] = NULL;
		}
	}

	array = new Piece* [cannum];
	for(i = 0; i < cannum; i++)
		array[i] = NULL;

	// �����`�ɂȂ���̂��܂Ƃ߂�
	changearray = new int* [7];
	for(i = 0; i < 7; i++)
		changearray[i] = new int [Shape::arraylen];
	for(i = 0, pnum = 0; i < cannum; i++) {
		if(candidate[i]) {
			// ���Ԃ��E���X�O�x��]�̔z������
			turn(candidate[i]->array, changearray[0]);
			leftrotate(changearray[0], changearray[1]);
			leftrotate(changearray[1], changearray[2]);
			leftrotate(changearray[2], changearray[3]);
			leftrotate(candidate[i]->array, changearray[4]);
			leftrotate(changearray[4], changearray[5]);
			leftrotate(changearray[5], changearray[6]);
			// �݂����������܂��o�^
			l = 0;
			array[pnum] = new Piece();
			array[pnum]->array[l] = candidate[i];
			candidate[i] = NULL;
			// ���Ԃ��E���X�O�x��]�̔z��Ɠ�������o�^
			for(j = 0; j < 7; j++) {
				for(k = i + 1; k < cannum; k++) {
					if(candidate[k]) {
						if(candidate[k]->issame(changearray[j])) {
							array[pnum]->array[++l] = candidate[k];
							candidate[k] = NULL;
							break;
						}
					}
				}
			}
			pnum++;
		}
	}
	for(i = 0; i < 7; i++)
		delete [] changearray[i];
	delete [] changearray;

	for(i = 0; i < cannum; i++)
		delete candidate[i];
	delete [] candidate;
}

// �f�X�g���N�^
Set::~Set()
{
	delete [] array;
	delete [] Shape::x;
	delete [] Shape::y;
}

// candidate[now]->array��0�`a-1�Ԗڂ���b�I���1�ɂ���
// candidate : shape�z��ւ̃|�C���^
// a : �����ΏۂƂ���array�̗v�f��
// b : 1�ɂ���array�̗v�f��
// now : �����ΏۂƂ���candidate�̓Y����
// �߂�l : ���ɏ����ΏۂƂ���candidate�̓Y����
int Set::makeShape(Shape** candidate, int a, int b, int now)
{
	int i, next;
	
	if(a == b) {
		for(i = 0; i < a; i++)
			candidate[now]->array[i] = 1;
		next = now + 1;
	} else if(b == 1) {
		next = now;
		for(i = 0; i < a; i++)
			candidate[next++]->array[i] = 1;
	} else {
		next = makeShape(candidate, a-1, b-1, now);
		for(i = now; i < next; i++)
			candidate[i]->array[a-1] = 1;		
		next = makeShape(candidate, a-1, b, next);
	}
	return next;
}

// a�𗠕Ԃ��ɂ����z���b�Ƃ���
// a : ���̔z��
// b : ���Ԃ��̌��ʂ�����z��
void Set::turn(int* a, int* b)
{
	int ymin, i, j;

	for(i = 0; i < Shape::arraylen; i++)
		b[i] = 0;
	// a��x=0�́��̒��ōŏ���y�����߂�
	ymin = 0;
	for(i = Shape::arraylen-mino+1; i < Shape::arraylen; i++) {
		if(a[i]) {
			ymin = Shape::y[i];
			break;
		}
	}
	// ���Ԃ��ɂ����z��̗v�f������
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i]) {
			j = (mino-Shape::x[i]-1)*(mino-Shape::x[i])-Shape::y[i]+ymin;
			if(j < Shape::arraylen)	// (0,0)��������Ȃ��̂ŁI
				b[j] = 1;
		}
	}
	j = (mino - 1) * mino + ymin;	// (0,0)�̕��I
	if(j < Shape::arraylen)
		b[j] = 1;
}

// a�����ɂX�O�x��]�����z���b�Ƃ���
// a : ���̔z��
// b : ��]�̌��ʂ�����z��
void Set::leftrotate(int* a, int* b)
{
	int xmax, ymax, i, j;

	// a�̂��ׂẮ��̒��ōő��y�����߂�
	ymax = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i] && (ymax < Shape::y[i]))
			ymax = Shape::y[i];
	}
	// a��y=ymax�́��̒��ōő��x�����߂�
	xmax = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i] && (Shape::y[i] == ymax) && (xmax < Shape::x[i]))
			xmax = Shape::x[i];
	}
	// ��]�����z��̗v�f������
	for(i = 0; i < Shape::arraylen; i++)
		b[i] = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i]) {
			j = (mino-ymax+Shape::y[i]-1)*(mino-ymax+Shape::y[i])+Shape::x[i]-xmax;
			if(j < Shape::arraylen)	// (0,0)��������Ȃ��̂ŁI
				b[j] = 1;
		}
	}
	j = (mino - ymax - 1) * (mino - ymax) - xmax;	// (0,0)�̕��I
	if(j < Shape::arraylen)
		b[j] = 1;
}