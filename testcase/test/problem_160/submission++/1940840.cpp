#include<bits/stdc++.h>
#define For(i,l,r) for(int i=l,i##_e=r;i<=i##_e;++i)
#define ReFor(i,r,l) for(int i=r,i##_e=l;i>=i##_e;--i)
const int N=50010;
const int M=61000000;
using namespace std;
int n,W;
int *f[N];
int fa[N],w[N],v[N],sub_w[N];
int pool[M];
vector<int> G[N];
void dfs(int x)
{
	sub_w[x]=min(w[x],W);
	if(w[x]<=W)f[x][w[x]]=max(f[x][w[x]],v[x]);
	for(auto y:G[x])
	{
		dfs(y);
		ReFor(W1,sub_w[x],w[x])
		{
			ReFor(W2,min((W-W1),sub_w[y]),w[y])
			{
				f[x][W1+W2]=max(f[x][W1+W2],(f[x][W1]+f[y][W2]));
			}
		}
		sub_w[x]=min((sub_w[x]+sub_w[y]),W);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>W;
	For(i,0,n)f[i]=pool+(i*(W+1));
	For(i,1,n){cin>>fa[i];G[fa[i]].emplace_back(i);}fa[0]=-1;
	For(i,1,n)cin>>w[i];For(i,1,n)cin>>v[i];
	dfs(0);
	int ans=0;For(i,0,W)ans=max(ans,f[0][i]);cout<<ans;return 0;
}