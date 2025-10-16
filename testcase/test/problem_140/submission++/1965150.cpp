#include <bits/stdc++.h>
using namespace std;
int Qread()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x;
}
typedef pair<int,int> pr;
#define ls s[x].lson
#define rs s[x].rson
namespace MH{
	struct Node{
		int poi,num,laz,dist;
		int lson,rson;
	}s[10010];
	void giv_laz(int x,int laz) {s[x].num+=laz,s[x].laz+=laz;}
	void pushdown(int x) {if(s[x].laz) giv_laz(ls,s[x].laz),giv_laz(rs,s[x].laz),s[x].laz=0;}
	void merge(int &x,int y)
	{
		if(x&&y)
		{
			if(s[x].num>s[y].num) swap(x,y);
			pushdown(x),merge(rs,y);
			if(s[ls].dist<s[rs].dist) swap(ls,rs);
			s[x].dist=s[rs].dist+1;
		}
		else x^=y;
	}
	void del(int &x){pushdown(x);merge(ls,rs);x=ls;}
}
#undef ls
#undef rs
namespace SET{
	priority_queue<pr,vector<pr>,greater<pr> > ins,del;
	void push(pr x){ins.push(x);}
	void pop(pr x){del.push(x);while(!del.empty()&&del.top()==ins.top()) del.pop(),ins.pop();}
	bool empty(){return ins.empty();}
	pr top(){return ins.top();}
}
struct DSU{
	int fa[110];
	void init(int n){for(int i=1;i<=n;i++) fa[i]=i;}
	int get_fa(int x){return x==fa[x]?x:fa[x]=get_fa(fa[x]);}
	void merge(int u,int v){fa[get_fa(v)]=fa[get_fa(u)];}
}S1,S2;
int poi_cnt;
int n,m,Rt,u,v,w;
int rt[110],fa[110],ans;
int main()
{
	n=Qread(),m=Qread(),Rt=Qread();
	S1.init(n),S2.init(n);
	for(int i=1;i<=m;i++)
	{
		u=Qread(),v=Qread(),w=Qread();
		if(u==v||v==Rt) continue;
		MH::s[++poi_cnt].dist=1,MH::s[poi_cnt].num=w; 
		MH::s[poi_cnt].poi=u;
		MH::merge(rt[v],poi_cnt);
	}

	

	for(int i=1;i<=n;i++) if(i!=Rt)
	{
		if(!rt[i]) return printf("-1\n"),0;
		SET::push(make_pair(MH::s[rt[i]].num,i));
	}
	for(int i=1;i<n;i++)
	{
		if(SET::empty()) return printf("-1\n"),0;
		u=SET::top().second,w=SET::top().first;

		ans+=w;MH::giv_laz(rt[u],-w);
		v=S1.get_fa(fa[u]=MH::s[rt[u]].poi);
		MH::del(rt[u]);SET::pop(make_pair(w,u));
		S1.merge(v,u);
		
		if(rt[v])
		{
			w=0;
			SET::pop(make_pair(MH::s[rt[v]].num,v));
			while(rt[v]&&S1.get_fa(MH::s[rt[v]].poi)==v)
			{
				w+=MH::s[rt[v]].num;u=S2.get_fa(MH::s[rt[v]].poi);
				MH::giv_laz(rt[v],-MH::s[rt[v]].num);
				MH::del(rt[v]);
				while(u!=v)
				{
					MH::merge(rt[v],rt[u]);
					S2.merge(v,u);
					u=S2.get_fa(fa[u]);
				}
			}
			if(rt[v])
			{
				MH::giv_laz(rt[v],w);
				SET::push(make_pair(MH::s[rt[v]].num,v));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}