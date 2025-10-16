#include<iostream>
#define ll long long
using namespace std;
int n,m,cnt;
ll basis[65],d[65];
bool zero;
void ins(ll x){
	if(x==0) return;
	for(int i=62;i>=0;i--)
		if((x>>i)&1){
			if(basis[i]==0){
				basis[i]=x;
				return;
			} else x^=basis[i];
		}
	zero=1;
}
bool chk(ll x){
	for(int i=62;i>=0;i--)
		if((x>>i)&1){
			if(!basis[i]) return 0;
			x^=basis[i];
		}
	return 1;
}
ll qmax(){
	ll ans=0;
	for(int i=62;i>=0;i--)
		ans=max(ans,ans^basis[i]);
	return ans;
}
ll qmin(){
	if(zero) return 0;
	for(int i=0;i<=62;i++)
		if(basis[i]) return basis[i];
}
void rebuild(){
	for(int i=62;i>=0;i--)
		for(int j=62;j>=0;j--){
			if(j==i) continue;
			if((basis[j]>>i)&1) basis[j]^=basis[i];
		}
	for(int i=0;i<=62;i++)
		if(basis[i]) d[cnt++]=basis[i];
}
ll kth(ll k){				
	if(zero) k--;
	if(k>=(1ll<<cnt)) return -1;
	ll ans=0;
	for(int i=0;i<cnt;i++)
		if((k>>i)&1) ans^=d[i];
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		ll x;
		cin>>x;
		ins(x);
	}
	rebuild();
	cin>>m;
	for(int i=1;i<=m;i++){
		ll x;
		cin>>x;
		cout<<kth(x)<<endl;
	}
	return 0;
}
