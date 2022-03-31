#include<iostream>

using namespace std;
void reverse(int A[],int lo,int hi)//递归模式
{
	if (lo < hi)
	{
		swap(A[lo], A[hi]);
		reverse(A, lo+1, hi-1);
	}
}
void reverse1(int A[], int lo, int hi)
{
	next:
	if (lo < hi)
	{		
		swap(A[lo], A[hi]);
		lo++;hi--;
		goto next;
	}
}
void reverse2(int A[], int lo, int hi)
{
	while (lo<hi)
	{
		swap(A[lo++], A[hi--]);
	}
	
}
int main()
{
	int A[] = { 1,2,3,4,5,6 };
	reverse2(A, 1, 3);
	for (int i = 0;i < 6;i++)
		cout << A[i];
	return 0;
}