#include<bits/stdc++.h>
#define LL long long
#define P pair<int,int>
#define fi first
#define se second
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e5+5;
int k,a[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>k;
	if(k==1) return cout<<"-1",0;int t=k,s=t;
	for(int i=2;i*i<=t;i++) if(t%i==0){s=s/i*(i-1);while(t%i==0) t/=i;}
	if(t^1) s=s/t*(t-1);a[s]=1;a[s<<1]=k-1;cout<<(s<<1)<<"\n";
	for(int i=0;i<=(s<<1);i++) cout<<a[i]<<" ";
	return 0;
}