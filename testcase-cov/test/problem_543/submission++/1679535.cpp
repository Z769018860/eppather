#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
#define pb push_back
#define inf 4557430888798830399
using namespace std;
ll T;
ll n,k; 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(ll i=1,x,y,z;i<=k;i++){
			cin>>x>>y>>z;
		}
		if((n*n-k)&1){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}