#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int N=3e6+5,mod=998244353;
int n,p;ll inv[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>p;
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=(p-p/i)*inv[p%i]%p;
	for(int i=1;i<=n;i++)
		cout<<inv[i]<<'\n';
	return 0;
}