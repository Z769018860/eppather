#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

int a[N];

int main()
{
	int n;
	cin>>n;
	cout<<n+1<<'\n';
	n++;
	if(n&1)cout<<n/2+1<<' ';
	for(int i=(n&1)?n-1:n,j=n/2;i>=1;i-=2,j--)cout<<j<<' '<<n-j+1<<' ';
	return 0;
}