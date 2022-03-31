#include<iostream>
using namespace std;
int fib(int n)//递归
{
    return(n < 2) ? n : fib(n - 1) + fib(n - 2);
}
int fib2(int n)//迭代
{
    int f = 0, g = 1;
    while (0<n--)
    {
        g = g + f;
        f = g - f;
    }
    return g;
}


int main()
{
    cout <<fib2(10)<< endl;
    return 0;
}