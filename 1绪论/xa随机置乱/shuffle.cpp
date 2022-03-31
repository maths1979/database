#include<iostream>
//#include<random>
using namespace std;
void shuffle(int A[],int n)
{
    while (1<n)
    {
        swap(A[rand() % n], A[--n]);
    }
    
}
int main()
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shuffle(A, 11);
    for (int i = 0; i < 11;i++)
        cout << A[i]<<"  ";
    return 0;
}