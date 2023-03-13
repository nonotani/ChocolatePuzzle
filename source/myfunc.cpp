#include "myfunc.h"

// 階乗n!
int factorial(int n)
{
	int ans = 1;
	if(n < 0)
		return -1;
	for(int i = 2; i <= n; i++)
		ans *= i;
	return ans;
}

// コンビネーションaCb
int combination(int a, int b)
{
	double ans = 1.0;

	for(int i = 0; i < b; i++) {
		ans *= a-i;
		ans /= i+1;
	}

	return (int)ans;
}
