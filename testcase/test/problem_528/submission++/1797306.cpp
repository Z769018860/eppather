#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int p=998244353;
int mu[10001000],tp=10000000,vis[10010000],pr[1001000],cnt;
ll n,m;
int main(){
	cin>>n>>m;
	mu[1]=1;
	for(int i=2;i<=tp;i++){
		if(!vis[i])mu[i]=-1,pr[++cnt]=i;
		for(int j=1;j<=cnt;j++){
			if(i*pr[j]>tp)break;
			if(i%pr[j]==0){
				mu[i*pr[j]]=0;
				vis[i*pr[j]]=1;
				break;
			}
			else mu[i*pr[j]]=-mu[i],vis[i*pr[j]]=1;
		}
	}
	ll ans=0;
	for(int d=1;1ll*d*d<=min(n,m);d++){
		ll d2=1ll*d*d;
		ans+=1ll*(n/d2%p)*(m/d2%p)%p*mu[d]%p;
		ans%=p;
	}
	cout<<(ans+p)%p;
}

