#include <bits/stdc++.h>
using namespace std;
const int N=2000;

int n,m,Ans;
bool a[N+9][N+9],b[N+9][N+9];
int U[N+9][N+9],D[N+9][N+9],L[N+9][N+9],R[N+9][N+9];

int siz;
struct Bit {
	int t[N+9];
	void clear() {memset(t,0,sizeof(t));}
	void add(int pos,int x) {for (;pos;pos-=pos&-pos) t[pos]+=x;}
	int operator [](int pos) {int res=0; for (;pos<=N;pos+=pos&-pos) res+=t[pos]; return res;}
} bit;
int c[N+9],d[N+9];
vector< pair< int, int > > qry[N+9];

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) for (int j=1;j<m;j++) cin>>a[i][j];
	for (int i=1;i<n;i++) for (int j=1;j<=m;j++) cin>>b[i][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			if (a[i][j]) L[i][j+1]=L[i][j]+1;
			if (b[i][j]) U[i+1][j]=U[i][j]+1;
		}
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--) {
			if (a[i][j]) R[i][j]=R[i][j+1]+1;
			if (b[i][j]) D[i][j]=D[i+1][j]+1;
		}
	for (int i=1-m;i<=n-1;i++) {
		int x=1,y=x-i,t=0;
		if (y<=0) y=1,x=y+i;
		while (x<=n && y<=m) {
			t++;
			c[t]=min(L[x][y],U[x][y]),d[t]=min(R[x][y],D[x][y]);
			if (t-1>0) qry[t-1].push_back(make_pair(t,1));
			if (t-c[t]-1>0) qry[t-c[t]-1].push_back(make_pair(t,-1));
			x++,y++;
		}
		int res=0;
		bit.clear();
		for (int j=1;j<=t;j++) {
			bit.add(d[j]+j,1);
			for (auto x:qry[j]) res+=bit[x.first]*x.second;
			qry[j].clear();
		}
		Ans+=res;
	}
	cout<<Ans<<endl;
	return 0;
}