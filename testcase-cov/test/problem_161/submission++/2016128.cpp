#include<bits/stdc++.h>

using namespace std;

#define ll long long
const int N=5000005;
const int p=1e9+7;
const int C=998244353;

int a[N],inv[N],s[N],sv[N];

void exgcd(int a, int b, int &d, int &x, int &y)
{
	if(b == 0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		exgcd(b,a%b,d,y,x);
		y -= x * (a/b);
	}
}

int powMod(int a, int n)
{
	int res=1;
	while(n)
	{
		if(n & 1) res = 1ll * res * a % p;
		a = 1ll * a * a % p;
		n >>= 1;
	}
	return res % p;
}

void Output(int a[],int n)
{
	for(int i=0; i<n; i++)
		cout<<a[i]<<endl;
}

int main()
{
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n;
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> a[i];
	
	s[0]=a[0];
	for(int i=1; i<n; i++)
		s[i] = 1ll * s[i-1]*a[i] % p;
	
	
	
	
	
	
	sv[n-1]=powMod(s[n-1],p-2);
	
	for(int i=n-2; i>=0; i--)
		sv[i]=1ll * a[i+1]*sv[i+1] % p;
	inv[0]=sv[0];
	for(int i=1; i<n; i++)
		inv[i]=1ll * s[i-1]*sv[i] % p;
	
	ll res=0,c=1;
	for(int i=n-1; i>=0; i--)
	{
		res = (res + (1ll * inv[i] * c % p)) % p;
		c = c * C % p;
	}
	cout << res <<endl;
	return 0;
}