#include <bits/stdc++.h>
#define int long long
#define N 2050
using namespace std;
int t1[N][N],t2[N][N],t3[N][N],t4[N][N],n,m,op,a,b,c,d,x;
int lowbit(int k){
	return k&-k;
}
void add(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=n;j+=lowbit(j)){
			t1[i][j]+=k;
			t2[i][j]+=k*x;
			t3[i][j]+=k*y;
			t4[i][j]+=k*x*y;
		}
	}
}
int ask(int x,int y){
	int a=0,b=0,c=0,d=0;
	for(int i=x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			a+=t1[i][j];
			b+=t2[i][j];
			c+=t3[i][j];
			d+=t4[i][j];
		}
	}
	return a*(x+1)*(y+1)-b*(y+1)-c*(x+1)+d;
}
signed main(){
	cin>>n>>m;
	while(cin>>op){
		if(op==1){
			cin>>a>>b>>c>>d>>x;
			add(a,b,x);
			add(a,d+1,-x);
			add(c+1,b,-x);
			add(c+1,d+1,x);
		}else{
			cin>>a>>b>>c>>d;
			cout<<ask(c,d)-ask(c,b-1)-ask(a-1,d)+ask(a-1,b-1)<<endl;
		}
	}
}