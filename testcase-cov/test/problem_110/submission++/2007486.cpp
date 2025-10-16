#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define endl "\n"
using namespace std;

typedef pair<int,int> PII;

const int N = 1010;

int n,p;

int qmi(int a,int b,int p)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;	
	}	
	return res;
} 

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> p;
	for (int i = 1;i<=n;i++) cout << qmi(i,p-2,p) << endl;
	
	return 0;
}