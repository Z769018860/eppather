#include<bits/stdc++.h>
using namespace std;
const long long p=998244352; 
long long f(long long x,long long k)
{
	long long s=1;
	while(k)
	{
		if(k&1)
		{
			s=s*x%p;
		}
		x=x*x%p;
		k>>=1;
	}
	return s%p;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long x,n;
	cin>>x>>n;
	long long k;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		long long result=f(x,k);
		cout<<result<<" ";
	}
	return 0;
 } 