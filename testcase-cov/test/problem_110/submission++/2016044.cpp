#include<bits/stdc++.h>

using namespace std;

#define ll long long
const int N=3000005;

int inv[N];

int main()
{
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n,p;
	cin >> n >> p;
	inv[1]=1;
	for(int i=2; i<=n; i++)
	{
		inv[i] = (ll)inv[p % i] * (p-p/i) % p;
	} 
	for(int i=1; i<=n; i++)
		cout<<inv[i]<<endl;
	return 0;
}