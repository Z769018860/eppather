#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int g=8e7+50;
int fa[g];
int find(int x){
	if(fa[x]==x)
		return x; 
	else{
		fa[x]=find(fa[x]);
		return fa[x];
	}
}
void add(int a, int b){
	int aa=find(a);
	int bb=find(b);
	fa[aa]=bb;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	string t;
	for(int i=0;i<m;i++){
		int op, a, b;
		cin>>op>>a>>b;
		if(op==0){
			add(a,b);
		}else{
			if(find(a)==find(b)){
				t+='1';
			}else{
				t+='0';
			}
		}
	}
	int ans=0, o=1;
	for(int i=t.length()-1;i>=0;i--){
		ans+=(t[i]-'0')*o;
		ans%=998244353;
		o=(o*2)%998244353;
	}
	cout<<ans;
}