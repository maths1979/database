#include<iostream>
int sum(int A[], int lo, int hi)//二分递归
{
    if (lo == hi) return A[lo];
    int mi = (lo + hi) >> 1;
    return sum(A, lo, mi) + sum(A, mi + 1, hi);
}
using std::cout;
int main()
{
	int A[] = { 1,2,3,4,5,6 };
	cout<<sum(A, 1, 3);	
	return 0;
}