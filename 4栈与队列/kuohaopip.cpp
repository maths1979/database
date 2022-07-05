#include"stack.h"
#include<iostream>
void trim(const char exp[], int& lo, int& hi)//删除exp[lo,hi]不含括号的最长前缀、后缀
{
    while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))lo++;
    while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))hi--;
}
int divide(const char exp[], int lo, int hi)//动态记录已经扫描的左右括号数目之差
//这个合适的mi定义为“直到左右括号对相等”，在左右括号队中有尽可能多的左右括号对
{
    int mi = lo;int crc = 1;
    while ((0<crc)&&(++mi<hi))
    {
        if (exp[mi] == ')')crc--;//匹配一对后减1
        if (exp[mi] == '(')crc++;//左括号增1
    }
    return mi;

}
bool paren(const char exp[], int lo, int hi)//二分递归
{
    trim(exp, lo, hi);
    if (lo > hi) return true;
    if (exp[lo] != '(')return false;
    if (exp[hi] != ')')return false;
    int mi = divide(exp, lo, hi);
    return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}
bool paren1(const char exp[], int lo, int hi) {//exp[lo,hi)
    //只含"()"的匹配
    Stack<char> S;
    for (int i = 0;i < hi - lo; i++)
    {
        if (exp[i] == '(') S.push(exp[i]);
        else if (!S.empty()) S.pop();
        else return false;
    }
    return S.empty();
}

bool paren2(const char exp[], int lo, int hi) {//迭代版
    //兼顾()[]{}三类括号
    Stack<char> S;
    for (int i = 0;i < hi - lo;i++)
        switch (exp[i])
        {
        case '{':case '(':case '[':S.push(exp[i]);break;
        case ')':if (S.empty() || S.pop() != '(') return false;break;
        case ']':if (S.empty() || '[' != S.pop())return false;break;
        case '}':if (S.empty() || '{' != S.pop())return false;break;
        default:break;
        }
    return S.empty();
}

int main()
{
    using std::cout;
    const char expression[] = "((())())";
    if (paren(expression, 0, sizeof(expression) - 1))
    {
        cout << "匹配";
    }
    else
        cout << "不匹配";

    return 0;
}
