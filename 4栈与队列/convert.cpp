#include"stack.h"
#include<iostream>

// void convert(Stack<char>& S, long long n, int base)//递归版
// {
//     static char digit[] = "0123456789ABCDEF";
//     if (0 < n) {
//         S.push(digit[n % base]);
//         convert(S, n / base, base);
//     }
// }


template<typename T>
void myprint(T& c)
{
    using std::cout;
    cout << c << " ";
}

void convert(Stack<char>& S, long long n, int base)//递归版
{
    static char digit[] = "0123456789ABCDEF";
    if (0 < n) {
        S.push(digit[n % base]);
        convert(S, n / base, base);
    }
}
void convert2(Stack<char>& S, long long n, int base)//迭代版
{
    static char digit[] = "0123456789ABCDEF";
    while (0<n)
    {
        S.push(digit[n % base]);
        n /= base;
    }
    
}
int main()
{
    using std::cout;
    using std::endl;

    Stack<char> S;
    convert2(S, 63, 16);
    while (!S.empty())
    {
        cout << S.pop() << " ";
    }
    
    return 0;
}