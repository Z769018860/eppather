#include<bits/stdc++.h>
using namespace std;
const int N=2e6;
int n,m,root,tot,ans,ANS;
struct Splay
{
	int f,s[2],a,cnt,size;
	void del()
	{
		f=s[0]=s[1]=a=cnt=size=0;
	}
}t[N];
int get(int x)
{
	return t[t[x].f].s[1]==x;
}
void pushup(int x)
{
	t[x].size=t[t[x].s[0]].size+t[t[x].s[1]].size+t[x].cnt;
}
void rotate(int x)
{
	int y=t[x].f,z=t[y].f;
	int k=get(x);
	t[z].s[get(y)]=x;
	t[x].f=z;
	t[y].f=x;
	t[y].s[k]=t[x].s[k^1];
	if(t[x].s[k^1])t[t[x].s[k^1]].f=y;
	t[x].s[k^1]=y;
	pushup(y);
	pushup(x);
}
void splay(int x,int r)
{
	for(int f;f=t[x].f,f!=r;rotate(x))
	{
		if(t[f].f!=r)rotate(get(f)==get(x)?f:x);
	}
	if(r==0)root=x;
}
int insert(int x)
{
	if(root==0)
	{
		root=++tot;
		t[tot].a=x;
		t[tot].cnt=t[tot].size=1;
		return tot;
	}
	int u=root,v=0;
	while(u)
	{
		v=u;
		if(t[u].a==x)
		{
			t[u].cnt++;
			t[u].size++;
			splay(u,0);
			return u;
		}
		else if(t[u].a>x)u=t[u].s[0];
		else u=t[u].s[1];
	}
	tot++;
	t[tot].f=v;t[tot].cnt=t[tot].size=1;
	t[tot].a=x;
	if(t[v].a>x)t[v].s[0]=tot;
	else t[v].s[1]=tot;
	splay(tot,0);
	return tot;
}
int getrank(int x)
{
	int u=root,cnt=0;
	while(u)
	{
		if(t[u].a<x)cnt+=t[u].size-t[t[u].s[1]].size,u=t[u].s[1];
		else if(t[u].a==x)return cnt+t[t[u].s[0]].size+1;
		else u=t[u].s[0];
	}
	return cnt+1;
}
int getnum(int rank)
{
	int u=root;
	while(u)
	{
		if(t[t[u].s[0]].size>=rank)u=t[u].s[0];
		else if(t[t[u].s[0]].size+t[u].cnt>=rank)
		{
			splay(u,0);
			return t[u].a;
		}
		else rank-=t[t[u].s[0]].size+t[u].cnt,u=t[u].s[1];
	}
	return -1;
}
int find(int x)
{
	int u=root;
	while(u)
	{
		if(t[u].a==x)
		{
			splay(u,0);
			return u;
		}
		else if(t[u].a>x)u=t[u].s[0];
		else u=t[u].s[1];
	}
	return -1;
}
int get_pre(int x)
{
	int u=find(x);
	u=t[u].s[0];
	while(t[u].s[1])u=t[u].s[1];
	return u;
}
int get_lat(int x)
{
	int u=find(x);
	u=t[u].s[1];
	while(t[u].s[0])u=t[u].s[0];
	return u;
}
void del(int x)
{
	int u=find(x);
	t[u].cnt--;
	pushup(u);
	if(t[u].cnt==0)
	{
		if(!t[u].s[0])
		{
			root=t[u].s[1];
			t[t[u].s[1]].f=0;
		}
		else if(!t[u].s[1])
		{
			root=t[u].s[0];
			t[t[u].s[0]].f=0;
		}
		else
		{
			root=t[u].s[0];
			t[t[u].s[0]].f=0;
			int v=t[u].s[0];
			while(t[v].s[1])v=t[v].s[1];
			t[v].s[1]=t[u].s[1];
			t[t[u].s[1]].f=v;
			splay(t[u].s[1],0);
		}
		t[u].del();
	}
}
void print(int x)
{
	if(!x)return;
	print(t[x].s[0]);
	cout<<t[x].a<<"*"<<t[x].cnt<<" ";
	print(t[x].s[1]);
}
int main()
{
	
	cin>>m;
	for(int i=1,a;i<=n;i++)
	{
		cin>>a,insert(a);
		
	}
	for(int i=1,op,x;i<=m;i++)
	{
		cin>>op>>x;
		
		if(op==1)insert(x);
		if(op==2)del(x);
		if(op==3)ANS^=(ans=getrank(x));
		if(op==4)ANS^=(ans=getnum(x));
		if(op==5)
		{
			insert(x);
			ANS^=(ans=t[get_pre(x)].a);
			del(x);
		}
		if(op==6)
		{
			insert(x);
			ANS^=(ans=t[get_lat(x)].a);
			del(x);
		}
		if(op>=3)cout<<ans<<endl;
		
	}
	
	return 0;
}
