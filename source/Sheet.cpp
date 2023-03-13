#include "Sheet.h"

// コンストラクタ
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

	// 結果ファイルオープン
	if((outFile = fopen("result.txt", "w")) == 0) {
		printf("Cannot open result.txt for output.\n");
		exit(-1);
	}
}

// デストラクタ
Sheet::~Sheet()
{
	for(int i = 0; i < row; i++)
		delete [] array[i];
	delete [] array;
	fclose(outFile);
	if(sol)
		delete sol;
}

// 解を求める
// a : 使うピースのセット
void Sheet::solve(Set* a)
{
	// 準備
	set_p = a;
	piece_a = new int [set_p->pnum];
	shape_a = new int [set_p->pnum];

	// メインの処理
	solve2(0);
	printf("解が%d個見つかりました！\n", sol_n);
	// 後片付け
	set_p = NULL;
	delete [] piece_a;
	delete [] shape_a;
	piece_a = NULL;
	shape_a = NULL;
}

// n番目のピースを決定
// n : 決定するピースの順番
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
				// 結果書込み
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

// ピースを置く
// n : n番目のピースに関して処理する
// 戻り値 : 置けたらtrue，置けなかったらfalse
bool Sheet::put_piece(int n)
{
	int r, c, i, x, y;

	// 前に使ったピースはダメ
	for(i = 0; (i < n) && (piece_a[i] != piece_a[n]); i++);
	if(i != n) {
		shape_a[n] = 7;
		return false;
	}
	// 開始位置を探す
	for(c = 0; c < col; c++) {
		for(r = 0; (r < row) && (array[r][c] != -1); r++);
		if(r != row)
			break;
	}
	// 置けるかどうかを確認
	for(i = 0; i < Shape::arraylen; i++) {
		if(set_p->array[piece_a[n]]->array[shape_a[n]]->array[i]) {
			y = r - Shape::y[i];
			x = c + Shape::x[i];
			if((y < 0) || (y >= row) || (x >= col) || (array[y][x] >= 0))
				break;
		}
	}
	// 置けるときは置く
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

// ピースを取り除く
// n : n番目のピースに関して処理する
void Sheet::del_piece(int n)
{
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			if(array[i][j] == piece_a[n])
				array[i][j] = -1;
		}
	}
}

// 次に処理するピースのピース番号と形番号を設定
// n : n番目のピースに関して処理する
// 戻り値 : 処理すべきピースが存在したらtrue，存在しなかったらfalse
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
