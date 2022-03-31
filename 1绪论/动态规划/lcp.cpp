#include<iostream>
#include<string>
using namespace std;
//最长公共子串长度
int lcs(char a[], char b[], int n, int m)//递归算法
{
    if (n == -1 or m == -1)
    {
        return 0;
    }
    else if (a[n] == b[m])
    {
        return lcs(a, b, n - 1, m - 1) + 1;
    }
    else {
        return max(lcs(a, b, n - 1, m), lcs(a, b, n, m - 1));
    }
}

int lcs1(char a[], char b[], int n, int m)//动态规划算法
{
    int i = 0, j = 0;
    int len[n + 1][m + 1];
    for (i = 0;i <= n;i++)len[i][0] = 0;
    for (j = 0;j <= m;j++)len[0][j] = 0;
    for (i = 1;i <= n;i++)
    {
        for (j = 1;j <= m;j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                len[i][j] = len[i - 1][j - 1] + 1;                
            }
            else
                len[i][j] =max(len[i][j - 1],len[i-1][j]);
        }

    }

    return len[n][m];
}
int main()
{
    char b[] = "didactical", a[] = "advantage";
    cout << lcs1(a,b,9,10) <<endl;
    return 0;
}