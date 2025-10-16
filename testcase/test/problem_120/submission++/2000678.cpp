#include<bits/stdc++.h>
using namespace std;
#define lc(x) tr[x].ls
#define rc(x) tr[x].rs
const int N=3e5+10;
struct node{int ls,rs,v,siz,rnd;}tr[N*20];int trlen,T,rt[N];
void update(int x){tr[x].siz=tr[lc(x)].siz+tr[rc(x)].siz+1;}
int newd(node no){tr[++trlen]=no;return trlen;}
int newd(int v){tr[++trlen]={0,0,v,1,rand()};return trlen;}
void split(int p,int k,int &x,int &y)
{
    if(!p)x=y=0;
    else
	{
        if(tr[lc(p)].siz>=k)
		{
            y=newd(tr[p]);
            split(lc(p),k,x,lc(y));
            update(y);
        }
		else
		{
            x=newd(tr[p]);
            split(rc(p),k-tr[lc(p)].siz-1,rc(x),y);
            update(x);
        }
    }
}

int merge(int x,int y)
{
	if(!x||!y) return x+y;
	if(tr[x].rnd<tr[y].rnd)
	{
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
int getkth(int p,int k)
{
	while(p)
	{
		if(tr[lc(p)].siz+1==k) return tr[p].v;
		
		if(tr[lc(p)].siz>=k)    p=lc(p);
		else k-=tr[lc(p)].siz+1,p=rc(p);
	}
}
int main()
{
    int n;scanf("%d",&n);
    rt[0]=0;T=trlen=0;
    int x,y,z,t,k,v,op;
    while(n--)
	{
        scanf("%d",&op);
        if(op==1)
		{
            scanf("%d%d%d",&t,&k,&v);rt[++T]=rt[t];
            split(rt[T],k-1,x,y);
            rt[T]=merge(merge(x,newd(v)),y);
        }
        if(op==2)
		{
            scanf("%d%d",&t,&k);rt[++T]=rt[t];
            split(rt[T],k,x,y);
            split(rt[T],k-1,x,z);
            rt[T]=merge(x,y);
        }
        if(op==3)
		{
            scanf("%d%d",&t,&k);
            printf("%d\n",getkth(rt[t],k));
        }
    }
    return 0;
}