#include<bits/stdc++.h>
using namespace std;
const int N = 4e6+5,mod=998244353;
int f[N]; 
void init()
{
	for(int i=0;i<N;i++){
		f[i]=i; 
	}
 } 
 int find(int i)
 {
 	if(f[i]==i)return i;
 	else return f[i]=find(f[i]);
 }
 void merge(int i,int j)
 {
 	int fi=find(i);
 	int fj=find(j);
 	f[fi]=fj;
 }
 signed main()
 {
 	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
 	init();
 	int n,m;
	long long ans=0;
 	cin>>n>>m;
	while(m-->0){
		int op,u,v;
		cin>>op>>u>>v;
		if(op==0){
			merge(u,v); 
		}
		else if(op==1){
			int res;
			if(find(u)==find(v))res=1;
			else res=0;
			ans=(ans*2+res)%mod;
		}
	}
	cout<<ans<<endl;
	return 0;
 }