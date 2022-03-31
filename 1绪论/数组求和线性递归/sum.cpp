#include<iostream>
int sum(int A[], int n)
{
    return n < 1 ? 0 : sum(A, n - 1)+A[n-1];
}
using  std::cout;
int main()
{
    int A[] = { 1,2,3,4,5,6 };
    cout << sum(A, 6);
    return 0;
}