#include<iostream>
int sumI(int A[], int n)
{
    int sum = 0;
    for (int i = 0;i < n;i++)
        sum += A[i];
    return sum;
}
using  std::cout;
int main()
{
    int A[] = { 1,2,3,4,5,6 };
    cout << sumI(A, 6);
    return 0;
}