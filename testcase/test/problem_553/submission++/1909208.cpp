#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define N 100000
#define M 30
using namespace std;
const long long inf=(long long)(1e18);
const int INF=(int)(2e9);
int read()
{
	char c=0;
	int sum=0;
	while (c<'0'||c>'9') c=getchar();
	while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
	return sum;
}
struct node
{
	int num;
	long long data;
	bool operator < (const node &t)const
	{
		return num!=t.num?num>t.num:data<t.data;	
	}
};
struct reads
{
	int v,l;
};
reads st[N+1];
int n,m,q,DP[M+1][2][2];
long long ans;
vector<node>dp[N+1];
int calc(int x,int y)
{
	for (int i=0;i<=M;++i)
		for (int op=0;op<=1;++op)
			for (int op2=0;op2<=1;++op2)
				DP[i][op][op2]=-INF;
	DP[0][0][0]=0;
	for (int i=1;i<=M;++i)
		for (int op=0;op<=1;++op)
			for (int op2=0;op2<=1;++op2)
				for (int opt=0,opts;opt<=1;++opt)
					for (int opt2=0,opts2;opt2<=1;++opt2)
					{
						if (((x>>(i-1))&1)!=opt) opts=(opt>((x>>(i-1))&1));
						else opts=op;
						if (((y>>(i-1))&1)!=opt2) opts2=(opt2>((y>>(i-1))&1));
						else opts2=op2;
						DP[i][opts][opts2]=max(DP[i][opts][opts2],DP[i-1][op][op2]|((opt^opt2)<<(i-1)));
					}
	return DP[M][0][0];
}
vector<node>F(vector<node>p,reads d)
{
	vector<node>q;
	for (int i=0;i<p.size();++i) q.push_back((node){calc(p[i].num,d.l),p[i].data+d.v});
	return q;
}
vector<node>operator + (vector<node>a,vector<node>b)
{
	for (int i=0;i<b.size();++i) a.push_back(b[i]);
	return a;
}
vector<node>solve(vector<node>p)
{
	long long sr=inf;
	vector<node>q;
	sort(p.begin(),p.end());
	for (int i=0;i<p.size();++i)
		if (p[i].data<sr)
			sr=p[i].data,q.push_back(p[i]);
	return q;
}
int main()
{
	int x;
	n=read(),m=read(),dp[0]={(node){0,0}};
	for (int i=1;i<=n;++i) st[i].v=read(),st[i].l=read();
	for (int i=1;i<=n;++i) dp[i]=solve(dp[i-1]+F(dp[i-1],st[i]));
	q=read();
	while (q--)
	{
		x=read(),ans=inf;
		for (int i=0;i<dp[n].size();++i)
			if (dp[n][i].num>=x)
				ans=min(ans,dp[n][i].data);
		printf("%lld\n",ans==inf?-1:ans);
	}
	return 0;
}
