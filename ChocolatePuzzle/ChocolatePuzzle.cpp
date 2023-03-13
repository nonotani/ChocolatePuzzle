// ChocolatePuzzle.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "Sheet.h"

int main()
{
	Set* a;
	Sheet* b;

	a = new Set(5);
	b = new Sheet(6, 10);
	b->solve(a);
	delete a;
	delete b;

	return 0;
}
