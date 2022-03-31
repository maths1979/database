#include<iostream>
using namespace std;
void max2(int A[], int lo, int hi, int& x1, int& x2)//迭代1
{
    int i;
    for (x1 = lo, i = lo + 1;i < hi;i++)
        if (A[x1] < A[i]) x1 = i;
    for (x2 = lo,i = lo + 1;i < x1;i++)
        if (A[x2] < A[i]) x2 = i;
    for (i = x1 + 1;i < hi;i++)
        if (A[x2] < A[i]) x2 = i;
}
void max2_1(int A[], int lo, int hi, int& x1, int& x2)//迭代2
{
    if (A[x1 = lo] < A[x2 = lo + 1])swap(x1, x2);
    for (int i = lo + 1;i < hi;i++)
        if (A[x2] < A[i])
            if (A[x1] < A[x2 = i]) swap(x1, x2);
}
void max2_2(int A[], int lo, int hi, int& x1, int& x2)//递归+分治
{
    if (hi < lo + 3) { trivial(A, lo, hi, x1, x2); return; }
    int mi = (lo + hi) / 2;
    int x1L, x2L;max2_2(A, lo, mi, x1L, x2L);
    int x1R, x2R;max2_2(A, mi, hi, x1R, x2R);
    if (A[x1L] >A[x2L])
    {
        x1 = x1L;
        x2 = A[x2L] >A[x1R] ? x2L : x1R;
    }
    else
    {
        x1 = x2R;
        x2 = A[x2R] > A[x1L] ? x2R : x1L;
    }
}
int main()
{
    // int A[] = { 1,12,3,44,5,6 };
    int A[] = { 1,2,3,4,5,6 };
    int a, b;
    max2_1(A, 0, 6, a, b);
    cout << a <<"  "<<b << endl;
    return 0;
}