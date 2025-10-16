#include <bits/stdc++.h>
#define lson (tr[i].ch[0])
#define rson (tr[i].ch[1])
using namespace std;
const int maxn=1e5+10,seed=chrono::steady_clock::now().time_since_epoch().count(); 
mt19937 rnd(seed);
struct node{
	int prio,val,siz,ch[2];

}tr[maxn];
int tot;
inline int newnode(int V)
{
	++tot;
	tr[tot].prio=rnd();
	tr[tot].val=V;
	tr[tot].siz=1;
	tr[tot].ch[0]=tr[tot].ch[1]=0; 
	return tot;
}
int rt,n,m;
inline void pushup(int i)
{
	tr[i].siz=1;
	tr[i].siz+=tr[lson].siz;
	tr[i].siz+=tr[rson].siz;
}
void splitv(int i,int v,int &x,int &y)
{
	if(!i){x=y=0;return;}
	if(tr[i].val<=v)splitv(tr[i].ch[1],v,tr[i].ch[1],y),x=i,pushup(x);
	else splitv(tr[i].ch[0],v,x,tr[i].ch[0]),y=i,pushup(y);
}
int merge(int x,int y)
{
	if(!x||!y)return x|y;
	if(tr[x].prio>tr[y].prio){tr[x].ch[1]=merge(tr[x].ch[1],y);pushup(x);return x;}
	else {tr[y].ch[0]=merge(x,tr[y].ch[0]);pushup(y);return y;}
}
void insert(int v)
{
	int L,R;
	splitv(rt,v,L,R);
	rt=merge(merge(L,newnode(v)),R);
}
void delet(int v)
{
	int L,R;
	splitv(rt,v,L,R);
	int tmp;
	splitv(L,v-1,L,tmp);
	tmp=merge(tr[tmp].ch[0],tr[tmp].ch[1]);
	rt=merge(merge(L,tmp),R); 
}
int queryrk(int i,int v)
{
	if(!i)return 1;
	if(tr[i].val>=v)return queryrk(lson,v);
	else return queryrk(rson,v)+tr[lson].siz+1; 
}
int queryval(int i,int k)
{
	if(!i)return 0;
	if(tr[lson].siz+1==k)return tr[i].val;
	else if(tr[lson].siz+1>k)return queryval(lson,k);
	else return queryval(rson,k-tr[lson].siz-1);
}
int findpre(int i,int x)
{
	if(!i)return -1e9; 
	if(tr[i].val<x)return max(findpre(rson,x),tr[i].val);
	else return findpre(lson,x);
}
int findnxt(int i,int x)
{
	if(!i)return 1e9;
	if(tr[i].val>x)return min(findnxt(lson,x),tr[i].val);
	else return findnxt(rson,x);
}
int main()
{


	cin>>m;
	while(m--)
	{
		int opt,x;
		cin>>opt>>x;
	
		if(opt==1)
			insert(x);
		else if(opt==2)
			delet(x);
		else if(opt==3)
			cout<<queryrk(rt,x)<<'\n';
		else if(opt==4)
			cout<<queryval(rt,x)<<'\n';
		else if(opt==5)
			cout<<findpre(rt,x)<<'\n';
		else cout<<findnxt(rt,x)<<'\n';
	}
}