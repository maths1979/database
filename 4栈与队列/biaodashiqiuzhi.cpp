//4.3.3 延迟缓存Page94
//表达式求值
#include<cmath>
#include<cstdlib>
#include"stack.h"
#include<iostream>
#define N_OPTR  9
typedef enum {ADD,SUB,MUL,DIV,POW,FAC,L_P,B_P,EOE} Operator;
const char pri[N_OPTR][N_OPTR] = {
    /*       +   -   *   /   ^   !   (   )   \0 */
    /* + */ '>','>','<','<','<','<','<','>','>',
    /* - */ '>','>','<','<','<','<','<','>','>',
    /* * */ '>','>','>','>','<','<','<','>','>',
    /* / */ '>','>','>','>','<','<','<','>','>',
    /* ^ */ '>','>','>','>','>','<','<','>','>',
    /* ! */ '>','>','>','>','>','>',' ','>','>',
    /* ( */ '<','<','<','<','<','<','<','=',' ',
    /* ) */ ' ',' ',' ',' ',' ',' ',' ',' ',' ',
    /* \0*/ '<','<','<','<','<','<','<',' ','='
};
bool isdigit(char a)
{
    const char digits[] = "1234567890";
    for (int i = 0;i < 10;i++)
        if (a == digits[i])return true;
    return false;
}
void readNumber(char*& p, Stack<float>& stk)
{
    stk.push((float)(*p - '0'));
    while (isdigit(*(++p)))
        stk.push(stk.pop() * 10 + (*p - '0'));
    if ('.' != *p)return;
    float fraction = 1;
    while (isdigit(*(++p)))
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
    

}
Operator getoptr(char op) {
    switch (op) {
    case '+':return ADD;break;
    case '-':return SUB;break;
    case '*':return MUL;break;
    case '/':return DIV;break;
    case '^':return POW;break;
    case '!':return FAC;break;
    case '(':return L_P;break;
    case ')':return B_P;break;
    case '\0':return EOE;break;
    default:exit(-1);
    }
}
char orderBetween(char top, char a)
{
    return pri[getoptr(top)][getoptr(a)];
}
float calcu(char optr, float opnd1, float opnd2) {
    float num;
    switch (optr)
    {
    case '+':
        num=opnd1 + opnd2;
    case '-':
        num=opnd1 - opnd2;
    case '*':
        num=opnd1 * opnd2;
    case '/':
        num=opnd1 / opnd2;
    case '^':
        num=powf(opnd1,opnd2);
    }
    return num;
}
float calcu(char optr, float opnd) {
    float num;
    switch (optr)
    {
    case '!':
        int i = 1;
        num = 1;
        while (i <= opnd)
        {
            num *= (i++);
        }
        break;
    }
    return num;
}
//重载append
void append(char*& RPN, float opnd)
{
 
}
void append(char*& RPN, char optr)
{
    int n = strlen(RPN);
    char* RPNn = new char[n+2];
    for (i = 0;i < n;i++)
        RPNn[i] = RPN[i];
    
}
float evaluate(char* S, char*& RPN) {
    Stack<float> opnd;Stack<char> optr;
    optr.push('\0');
    while (!optr.empty())
    {
        if (isdigit(*S)) {
            readNumber(S, opnd);//隐含了操作数的push操作
            //append(RPN, opnd.top());
        }
        else {
            switch (orderBetween(optr.top(),*S))
            {
            case '<':
                optr.push(*S);S++;
                break;
            case '>':
            {char op = optr.pop();
            if ('!' == op) {
                float pOpnd = opnd.pop();
                opnd.push(calcu(op, pOpnd));
            }
            else {
                float op2 = opnd.pop(), op1 = opnd.pop();
                opnd.push(calcu(op, op1, op2));
            }
            break;
            }
            case '=':
                optr.pop();S++;
                break;
            default:
                exit(-1);
            }
        }
    }
    return opnd.pop();
}
int main()
{
    
    return 0;
}