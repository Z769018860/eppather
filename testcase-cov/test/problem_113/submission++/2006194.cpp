#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n;ll p[55];
void ins(ll x){
	for(int i=50;i>=0;i--)
		if(x>>i&1){
			if(p[i])x^=p[i];
			else{
				p[i]=x;
				break;
			}
		}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		ll a;
		cin>>a;
		ins(a);
	}
	ll ans=0;
	for(int i=50;i>=0;i--)
		if(p[i]&&!(ans>>i&1))
			ans^=p[i];
	cout<<ans<<'\n';
	return 0;
}