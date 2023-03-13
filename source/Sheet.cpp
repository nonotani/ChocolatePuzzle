#include "Sheet.h"

// �R���X�g���N�^
Sheet::Sheet(int arow, int acol)
{
	row = arow;
	col = acol;
	Solution::row = row;
	Solution::col = col;
	sol_n = 0;
	sol = NULL;
	array = new int* [row];
	for(int i = 0; i < row; i++) {
		array[i] = new int [col];
		for(int j = 0; j < col; j++)
			array[i][j] = -1;
	}
	set_p = NULL;
	piece_a = NULL;
	shape_a = NULL;

	// ���ʃt�@�C���I�[�v��
	if((outFile = fopen("result.txt", "w")) == 0) {
		printf("Cannot open result.txt for output.\n");
		exit(-1);
	}
}

// �f�X�g���N�^
Sheet::~Sheet()
{
	for(int i = 0; i < row; i++)
		delete [] array[i];
	delete [] array;
	fclose(outFile);
	if(sol)
		delete sol;
}

// �������߂�
// a : �g���s�[�X�̃Z�b�g
void Sheet::solve(Set* a)
{
	// ����
	set_p = a;
	piece_a = new int [set_p->pnum];
	shape_a = new int [set_p->pnum];

	// ���C���̏���
	solve2(0);
	printf("����%d������܂����I\n", sol_n);
	// ��Еt��
	set_p = NULL;
	delete [] piece_a;
	delete [] shape_a;
	piece_a = NULL;
	shape_a = NULL;
}

// n�Ԗڂ̃s�[�X������
// n : ���肷��s�[�X�̏���
void Sheet::solve2(int n)
{
	piece_a[n] = 0;
	shape_a[n] = 0;
	do {
		if(put_piece(n)) {
			if(n == set_p->pnum-1) {
				if(!sol)
					sol = new Solution(array);
				else if(!sol->add(array))
					break;
				// ���ʏ�����
				sol_n++;
				fprintf(outFile, "-----%d-----\n", sol_n);
				for(int i = 0; i < row; i++) {
					for(int j = 0; j < col; j++) {
						if(array[i][j] < 10)
							fprintf(outFile, " ");
						fprintf(outFile, "%d", array[i][j]);
					}
					fprintf(outFile, "\n");
				}
				del_piece(n);
				break;
			} else {
				solve2(n+1);
				del_piece(n);
			}
		}
	} while(next_piece(n));
}

// �s�[�X��u��
// n : n�Ԗڂ̃s�[�X�Ɋւ��ď�������
// �߂�l : �u������true�C�u���Ȃ�������false
bool Sheet::put_piece(int n)
{
	int r, c, i, x, y;

	// �O�Ɏg�����s�[�X�̓_��
	for(i = 0; (i < n) && (piece_a[i] != piece_a[n]); i++);
	if(i != n) {
		shape_a[n] = 7;
		return false;
	}
	// �J�n�ʒu��T��
	for(c = 0; c < col; c++) {
		for(r = 0; (r < row) && (array[r][c] != -1); r++);
		if(r != row)
			break;
	}
	// �u���邩�ǂ������m�F
	for(i = 0; i < Shape::arraylen; i++) {
		if(set_p->array[piece_a[n]]->array[shape_a[n]]->array[i]) {
			y = r - Shape::y[i];
			x = c + Shape::x[i];
			if((y < 0) || (y >= row) || (x >= col) || (array[y][x] >= 0))
				break;
		}
	}
	// �u����Ƃ��͒u��
	if(i == Shape::arraylen) {
		array[r][c] = piece_a[n];
		for(i = 0; i < Shape::arraylen; i++) {
			if(set_p->array[piece_a[n]]->array[shape_a[n]]->array[i])
				array[r-Shape::y[i]][c+Shape::x[i]] = piece_a[n];
		}
		return true;
	} else {
		return false;
	}
}

// �s�[�X����菜��
// n : n�Ԗڂ̃s�[�X�Ɋւ��ď�������
void Sheet::del_piece(int n)
{
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			if(array[i][j] == piece_a[n])
				array[i][j] = -1;
		}
	}
}

// ���ɏ�������s�[�X�̃s�[�X�ԍ��ƌ`�ԍ���ݒ�
// n : n�Ԗڂ̃s�[�X�Ɋւ��ď�������
// �߂�l : �������ׂ��s�[�X�����݂�����true�C���݂��Ȃ�������false
bool Sheet::next_piece(int n)
{
	shape_a[n]++;
	if((shape_a[n] == 8) || !set_p->array[piece_a[n]]->array[shape_a[n]]) {
		piece_a[n]++;
		if(piece_a[n] == set_p->pnum) {
			return false;
		} else {
			shape_a[n] = 0;
			return true;
		}
	} else {
		return true;
	}
}
