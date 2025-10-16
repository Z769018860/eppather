#include <bits/stdc++.h>
#define int long long
using namespace std;
int t[4100][4100],n,m,op,x,y,a,b,c,d,k;
int lowbit(int k){
	return k&-k;
}
void add(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=m;j+=lowbit(j)){
			t[i][j]+=k;
		}
	}
}
int ask(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			res+=t[i][j];
		}
	}
	return res;
}
signed main(){
	cin>>n>>m;
	while(cin>>op){
		if(op==1){
			cin>>a>>b>>c>>d>>k;
			add(a,b,k);
			add(c+1,b,-k);
			add(a,d+1,-k);
			add(c+1,d+1,k);
		}else{
			cin>>x>>y;
			cout<<ask(x,y)<<endl;
		} 
	}
}