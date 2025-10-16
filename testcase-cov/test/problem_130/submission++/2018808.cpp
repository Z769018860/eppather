#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,q,s[N],a,t,l,r;
void build(int x,int v){
	while(x<=n){
		s[x]+=v;
		x+=x&(-x);
	}	
}
int find(int r1){
	int ans=0;
	while(r1>=1){
		ans+=s[r1];
		r1-=r1&(-r1);
	}
	return ans;		
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a;build(i,a);
	}
	for(int i=1;i<=q;i++){
		cin>>t;
		if(t==1){
			cin>>l>>r;
			build(l,r);
		}
		else{
			cin>>l>>r;
			cout<<find(r)-find(l-1)<<endl;
		}
	}
}