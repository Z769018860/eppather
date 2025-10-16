#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,p;
int a[55],b[55][3005],len[55];
const int mod=19260817;
unordered_map<int,int>mp;
  
int F(int m,int k){
	if(!m)return k==0;
	int id=m*mod+k;
    if(mp.count(id))return mp[id];
	int ans=0,a=m%p,c=m/p,d=k/p;
	for(int i=k%p;i<len[a]&&i<=k;i+=p,--d)if(b[a][i])ans+=F(c,d)*b[a][i];
	return mp[id]=ans%p;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>p;
	for(int i=0;i<=n;++i)cin>>a[i];
	b[0][0]=len[0]=1;
	for(int i=1;i<p;++i){
        len[i]=len[i-1]+n;
		for(int j=0;j<len[i];++j){
            int val=0;
			for(int k=0;k<=min(n,j);++k)val+=a[k]*b[i-1][j-k];
			b[i][j]=val%p;
		}
	}
	int T;
    cin>>T;
	while(T--){
		int m,k;
        cin>>m>>k;
		cout<<F(m,k)<<'\n';
	}
	return 0;
}
