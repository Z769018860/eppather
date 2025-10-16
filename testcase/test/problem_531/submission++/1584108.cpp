#include<bits/stdc++.h>
using namespace std;

const int N=1e6+7;
char str[3][10]={"0\n","1\n","2\n"};
int n,q,id[N],rk[N],stk[N],top,sg[N],Clen,len,f[N];
bool vis[N];
vector<int> G[N];
set<int> arr;

void findcir(int u)
{
	if(vis[u])
	{
		Clen=top;
		for(int i=1;i<=top;++i)	id[i]=stk[i],rk[id[i]]=i;
		return;
	}
	vis[u]=1,stk[++top]=u;
	for(int v:G[u])findcir(v);
	--top;
}

void dfs(int u)
{
	for(int v:G[u])if(rk[v]==0)
	{
		dfs(v);
		if(sg[v]==0) sg[u]=1;
	}
}

inline int find(int l,int r)
{
	if(l>r) return r+1;
	auto it=arr.lower_bound(l);
	return it!=arr.end()?min(r+1,*it):r+1;
}
inline int calc(int l,int r)
{
	int x=find(l,r);
	return ((x-l)&1)==0;
}
inline int mg(int l1,int r1,int l2,int r2)
{
	int x=find(l2,r2),y=find(l1,r1);
	if(y<=r1) return ((y-l1)&1)==0;
	return ((x+r1-l1)&1)==0;
}

inline bool chk(int l,int r)
{
	if(l>r) return 0;
	int x=find(l,r);
	if(x<=r) 
	{
		cout<<str[(len+x-l+1)&1];
		return 1;
	}
	len+=r-l+1;
	return 0;
}

int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int i,l,r,x,S,u,v;
	
	cin>>n>>q;
	for(i=1;i<=n;++i) cin>>f[i],G[f[i]].push_back(i);
	
	findcir(1);
	for(i=1;i<=Clen;++i) dfs(id[i]);
	for(i=1;i<=Clen;++i)if(sg[id[i]]) arr.insert(i);
	
	S=rk[1];
	while(q--)
	{
		cin>>u>>v;
		if(S==0){cout<<str[sg[1]];continue;}
		
		len=0;
		r=rk[f[u]],l=rk[v];
		if(arr.find(l)!=arr.end()) arr.erase(l);
		
		if(l<=r)
		{
			if(l<S&&S<=r)
			{
				cout<<str[calc(S,r)];
				goto flag;
			}
			
			if(sg[v]) arr.insert(l),x=1;
			else if(x=calc(l,r),x) arr.insert(l);
			++r;
			
			if(S<=l)
			{
				if(!chk(S,l)&&!chk(r,Clen)&&!chk(1,S-1)) cout<<str[2];
			}
			else
			{
				if(!chk(S,Clen)&&!chk(1,l)&&!chk(r,S-1)) cout<<str[2];
			}
			
			if(x) arr.erase(l);
		}
		else
		{
			if(S<=r)
			{
				cout<<str[calc(S,r)];
				goto flag;
			}
			if(S>l)
			{
				cout<<str[mg(S,Clen,1,r)];
				goto flag;
			}
			
			if(sg[v]) arr.insert(l),x=1;
			else if(x=mg(l,Clen,1,r),x) arr.insert(l);
			r=rk[u];
			
			if(!chk(S,l)&&!chk(r,S-1)) cout<<str[2];
			
			if(x) arr.erase(l);
		}
		
		flag:if(sg[v]) arr.insert(l); 
	}

	return 0;
}