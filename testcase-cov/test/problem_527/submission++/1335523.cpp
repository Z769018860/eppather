#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=1005;
int n,m,a[N][N],b[N][N],ri[N][N],le[N][N],up[N][N],dw[N][N];
namespace xuanyi{

template<class T>
struct fenwick{
	int n;
	vector<T>t;
	fenwick(int n):n(n),t(n){}
	void add(int x,const T&y){ 
		++x;
		for(int i=x;i<=n;i+=i&-i)t[i-1]+=y;
	}
	void add(int l,int r,const T&x){ 
		add(l,x);
		add(r+1,-x);
	}
	T query(int x){
		if(x<0)return 0;
		++x;
		T y=0;
		for(int i=x;i;i&=i-1)y+=t[i-1];
		return y;
	}
	T query(int l,int r){ 
		return query(r)-query(l-1);
	}
};

}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)rep(j,1,m-1)scanf("%d",&a[i][j]);
	rep(i,1,n-1)rep(j,1,m)scanf("%d",&b[i][j]);
	rep(i,1,n){
		le[i][1]=0;
		rep(j,2,m){
			le[i][j]=a[i][j-1]?le[i][j-1]+1:0;
		}
		ri[i][m]=0;
		per(j,m-1,1){
			ri[i][j]=a[i][j]?ri[i][j+1]+1:0;
		}
	}
	rep(j,1,m){
		up[1][j]=0;
		rep(i,2,n){
			up[i][j]=b[i-1][j]?up[i-1][j]+1:0;
		}
		dw[n][j]=0;
		per(i,n-1,1){
			dw[i][j]=b[i][j]?dw[i+1][j]+1:0;
		}
	}
	int ans=0;
	rep(z,1-m,n-1){
		xuanyi::fenwick<int>tr(n+1);
		multiset<pair<int,int> >S;
		rep(x,max(1,z+1),n){
			while(!S.empty()&&get<0>(*S.begin())<=x){
				tr.add(get<1>(*S.begin()),-1);
				S.erase(S.begin());
			}
			int y=x-z;
			if(y<1||y>m)break;
			ans+=tr.query(x-min(le[x][y],up[x][y]),x);
			int cur=min(ri[x][y],dw[x][y]);
			tr.add(x,1);
			S.insert({x+cur+1,x});
		}
	}
	printf("%d\n",ans);
	return 0;
}