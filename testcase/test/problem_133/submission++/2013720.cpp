#include<bits/stdc++.h>
using namespace std;
long long tree[5009][5009],n,m;
int xa,ya,xb,yb,x,y,k,op;
int lowbit(int x){
	return x & -x;
}
void update(int x,int y,int p){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=m;j+=lowbit(j)){
			tree[i][j]+=p;
		}
	}
}
long long query(int x,int y){
	long long ans=0;
	for(int i=x;i>0;i-=lowbit(i)){
		for(int j=y;j>0;j-=lowbit(j)){
			ans+=tree[i][j];
		}
	}
	return ans;
}
long long sum(int xa,int ya,int xb,int yb){
	return query(xb,yb)-query(xa-1,yb)-query(xb,ya-1)+query(xa-1,ya-1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	while(cin>>op){
		if(op==1){
			cin>>x>>y>>k;
			update(x,y,k);
		}
		else{
			cin>>xa>>ya>>xb>>yb;
			cout<<sum(xa,ya,xb,yb)<<'\n';
		}
	}
}