#include "Set.h"

// コンストラクタ
// amino : １ピースの■の個数
Set::Set(int amino)
{
	int i, j, k, l, cannum;
	Shape** candidate;
	int** changearray;

	mino = amino;
	// shapeクラスのstatic変数を設定
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

	// ピースの形を作ってみる
	cannum = combination(Shape::arraylen, mino-1);
	candidate = new Shape* [cannum];
	for(i = 0; i < cannum; i++)
		candidate[i] = new Shape();
	makeShape(candidate, candidate[0]->arraylen, mino-1, 0);

	// 隣接していない■があるピースを削除
	for(i = 0; i < cannum; i++) {
		if(!candidate[i]->iscorrect()) {
			delete candidate[i];
			candidate[i] = NULL;
		}
	}

	array = new Piece* [cannum];
	for(i = 0; i < cannum; i++)
		array[i] = NULL;

	// 同じ形になるものをまとめる
	changearray = new int* [7];
	for(i = 0; i < 7; i++)
		changearray[i] = new int [Shape::arraylen];
	for(i = 0, pnum = 0; i < cannum; i++) {
		if(candidate[i]) {
			// 裏返し・左９０度回転の配列を作る
			turn(candidate[i]->array, changearray[0]);
			leftrotate(changearray[0], changearray[1]);
			leftrotate(changearray[1], changearray[2]);
			leftrotate(changearray[2], changearray[3]);
			leftrotate(candidate[i]->array, changearray[4]);
			leftrotate(changearray[4], changearray[5]);
			leftrotate(changearray[5], changearray[6]);
			// みつかった候補をまず登録
			l = 0;
			array[pnum] = new Piece();
			array[pnum]->array[l] = candidate[i];
			candidate[i] = NULL;
			// 裏返し・左９０度回転の配列と同じ候補を登録
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

// デストラクタ
Set::~Set()
{
	delete [] array;
	delete [] Shape::x;
	delete [] Shape::y;
}

// candidate[now]->arrayの0～a-1番目からb個選んで1にする
// candidate : shape配列へのポインタ
// a : 処理対象とするarrayの要素数
// b : 1にするarrayの要素数
// now : 処理対象とするcandidateの添え字
// 戻り値 : 次に処理対象とするcandidateの添え字
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

// aを裏返しにした配列をbとする
// a : 元の配列
// b : 裏返しの結果を入れる配列
void Set::turn(int* a, int* b)
{
	int ymin, i, j;

	for(i = 0; i < Shape::arraylen; i++)
		b[i] = 0;
	// aのx=0の■の中で最小のyを求める
	ymin = 0;
	for(i = Shape::arraylen-mino+1; i < Shape::arraylen; i++) {
		if(a[i]) {
			ymin = Shape::y[i];
			break;
		}
	}
	// 裏返しにした配列の要素を決定
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i]) {
			j = (mino-Shape::x[i]-1)*(mino-Shape::x[i])-Shape::y[i]+ymin;
			if(j < Shape::arraylen)	// (0,0)かもしれないので！
				b[j] = 1;
		}
	}
	j = (mino - 1) * mino + ymin;	// (0,0)の分！
	if(j < Shape::arraylen)
		b[j] = 1;
}

// aを左に９０度回転した配列をbとする
// a : 元の配列
// b : 回転の結果を入れる配列
void Set::leftrotate(int* a, int* b)
{
	int xmax, ymax, i, j;

	// aのすべての■の中で最大のyを求める
	ymax = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i] && (ymax < Shape::y[i]))
			ymax = Shape::y[i];
	}
	// aのy=ymaxの■の中で最大のxを求める
	xmax = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i] && (Shape::y[i] == ymax) && (xmax < Shape::x[i]))
			xmax = Shape::x[i];
	}
	// 回転した配列の要素を決定
	for(i = 0; i < Shape::arraylen; i++)
		b[i] = 0;
	for(i = 0; i < Shape::arraylen; i++) {
		if(a[i]) {
			j = (mino-ymax+Shape::y[i]-1)*(mino-ymax+Shape::y[i])+Shape::x[i]-xmax;
			if(j < Shape::arraylen)	// (0,0)かもしれないので！
				b[j] = 1;
		}
	}
	j = (mino - ymax - 1) * (mino - ymax) - xmax;	// (0,0)の分！
	if(j < Shape::arraylen)
		b[j] = 1;
}