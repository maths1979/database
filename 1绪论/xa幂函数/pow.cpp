#include<iostream>
using namespace std;
long long power(long long a,long long n)//平凡实现
{
    pow = 1;
    while (0<n)
    {
        pow *= a;n--;
    }
    return pow;

}
long long power(long long a,long long n)//线性迭代版
{
    int pow = 1;int p = a;
    while (0<n)
    {
        if (n % 1)
        {
            pow *= p;
        }
        n >> 1;
        p *= p;
    }
    
}

long long power(long long a,long long n)//线性递归版
{
    
}