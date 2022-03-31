#include<iostream>
using namespace std;
int shift(int* A, int n, int s, int k);
//将数组A[0,n)中元素向左循环移动k个单元
//蛮力版，反复以1为间距循环左移
void reverse(int* A, int lo, int hi)
{
    while (lo<hi)
    {
        swap(A[lo++], A[--hi]);
    }
    
}
void shift0(int* A, int n, int k)
{
    while (k--) { shift(A, n, 0, 1); }
}
int shift(int* A, int n, int s, int k)
//完成从s开始的，每隔k个位置的元素前移
{
    int b = A[s];int i = s, j = (s + k) % n; int mov = 0;
    while (s!=j)
    {
        A[i] = A[j];i = j;j = (j + k) % n;mov++;
    }
    A[i] = b;
    return mov+1;
}

void shift1(int* A,int n, int k)//迭代版
{
    for (int s = 0, mov = 0;mov < n;s++)
        mov += shift(A, n, s, k);
}

void shift2(int* A, int n, int k)//倒置版
{
    reverse(A,0,k);
    reverse(A,k,n);
    reverse(A,0,n);
}
int main()
{
    int A[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
    shift2(A, 20, 6);
    for (int i = 0;i < 20;i++)
        cout << *(A + i);
    return 0;
}