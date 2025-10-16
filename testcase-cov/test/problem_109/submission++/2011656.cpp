

#include <iostream>
#include <math.h>
using namespace std;
#define int long long
int n,m,k=1,ern,num;
const int N=4e6+5;
const int M=8e6+5;
const int mod=998244353;
int fa[N];
int st[M];
struct 	node{
	int t,x,y;
}a[N];
int find(int i){
	if(fa[i]==i)	return i;
	else {
        fa[i]=find(fa[i]);
        return fa[i];
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
        int t,x,y;
		cin>>t>>x>>y;
		if(t){
			if(find(x)==find(y)){
				st[k++]=1;
			}else{
				st[k++]=0;
			}
		}else{
			int fx=find(x);
			int fy=find(y);
			if(fx!=fy){
				fa[fx]=fy;
			}
		}
	}
	k-=1;
	int ans=0;
	for(int i=1;i<=k;i++){
        if(st[i]){
            ans=(ans*2+1)%mod;
        }
        else ans=ans*2%mod;
	}
	cout<< ans%mod <<endl;
	return 0;
}

