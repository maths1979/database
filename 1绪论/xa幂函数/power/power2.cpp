#include<iostream>
inline long long sqr(long long a){return a*a;}
long long power2(int n)//递归模式
{
	if(0==n)return 1;
	return (n&1)?sqr(power2(n>>1))<<1:sqr(power2(n>>1));
}
long long power2BF_I(int n)//蛮力迭代版
{
	long long pow=1;
	while(0<n--)
		pow<<=1;
	return pow;
}
int power(int a,int n)
{
	int pow=1;int p=a;
	while(0<n)
	{
		if(n&1)pow*=p;
		n>>=1;
		p*=p;
	}
	return pow;
}
using std::cout;
int main()
{
	cout<<power(5,60);
	return 0;
}