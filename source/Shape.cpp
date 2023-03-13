#include "Shape.h"

int* Shape::x = NULL;
int* Shape::y = NULL;
int Shape::mino = 0;
int Shape::arraylen = 0;

// コンストラクタ
Shape::Shape()
{
	int i;

	array = new int [arraylen];
	for(i = 0; i < arraylen; i++)
		array[i] = 0;
}

// デストラクタ
Shape::~Shape()
{
	delete [] array;
}

// すべての■が隣接しているかどうかをチェックする
// 戻り値 : 隣接していたらtrue，隣接していなかったらfalse
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

// (ax,ay)の隣接■にまだチェックしていない1があったら2にする
// ax : 処理対象のｘ座標
// ay : 処理対象のｙ座標
void Shape::next(int ax, int ay)
{
	next2(ax, ay+1);
	next2(ax, ay-1);
	next2(ax+1, ay);
	next2(ax-1, ay);
}

// (ax,ay)が1だったら2にして再帰呼出し
// ax : 処理対象のｘ座標
// ay : 処理対象のｙ座標
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

// arrayとaが同じ配列かどうかをチェック
// a : 比較対象の配列
// 戻り値 : 同じときtrue，違うときfalse
bool Shape::issame(int* a)
{
	int i;

	for(i = 0; (i < arraylen) && ((!array[i] && !a[i]) || (array[i] && a[i])); i++);
	if(i == arraylen)
		return true;
	else
		return false;
}