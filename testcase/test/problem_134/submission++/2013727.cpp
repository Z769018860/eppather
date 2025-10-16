#include<bits/stdc++.h>
using namespace std;
long long tree[5009][5009],n,m;
int a,b,c,d,x,y,k,op;
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
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	while(cin>>op){
		if(op==1){
			cin>>a>>b>>c>>d>>k;
			update(a,b,k);
			update(a,d+1,-k);
			update(c+1,b,-k);
			update(c+1,d+1,k);
		}
		else{
			cin>>x>>y;
			cout<<query(x,y)<<'\n';
		}
	}
}