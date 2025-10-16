#include<bits/stdc++.h>
#define ll long long
#define deb(x) cerr<<"deb line"<<__LINE__<<": "<<#x<<"="<<x<<"\n"
using namespace std;
inline ll read()
{
	ll sum=0,l=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')l=-1;c=getchar();}
	while(isdigit(c)){sum=sum*10+c-'0';c=getchar();}
	return sum*l;
}
const ll N=2e18;
ll tl[2001000],tr[2001000],tg[2001000],a[1001000][2],hf[100][2];
struct line
{
	ll k,b;
	line operator+(const line &x)const
	{
		if(b>x.b||(b==x.b&&k>x.k))
		{
			return (line){k,b};
		}
		else
		{
			return (line){x.k,x.b};
		}
	}
};
pair<line,ll> max(line a,line b)
{
    if(a.k<b.k||(a.k==b.k&&a.b<b.b))swap(a,b);
    if(a.b>=b.b){return make_pair(a,N);}
    return make_pair(b,(b.b-a.b)/(a.k-b.k));
}
struct Node
{
	line ans;ll x,id;
    Node operator+(const Node &y)const
    {
        Node t;t.x=min(x,y.x);
        pair<line,ll> up=max(ans,y.ans);
        t.x=min(t.x,up.second);
        t.ans=up.first;
        if(t.ans.b==ans.b&&t.ans.k==ans.k)
        {
        	t.id=id;
		}
		else
		{
			t.id=y.id;
		}
        return t;
    }
}ts[2001000];
void Build(ll x,ll l,ll r)
{
	tl[x]=l;
	tr[x]=r;
	if(l==r)
	{
		line t=(line){a[l][0],a[l][1]};
		ts[x].ans=t;
		ts[x].id=l;
		ts[x].x=N;
		return;
	}
	Build(x*2,l,(l+r)/2);
	Build(x*2+1,(l+r)/2+1,r);
	ts[x]=ts[x*2]+ts[x*2+1];
}
void Update(ll x,ll w)
{
	tg[x]+=w;
	ts[x].x-=w;
	ts[x].ans.b+=w*ts[x].ans.k;
}
void Update2(ll x)
{
	ts[x].ans.b=max(ts[x*2].ans.b,ts[x*2+1].ans.b);
	if(ts[x*2].ans.b==ts[x].ans.b)
	{
		ts[x].id=ts[x*2].id;
	}
	else
	{
		ts[x].id=ts[x*2+1].id;
	}
}
void upd(ll x,ll w)
{
	if(w>ts[x].x)
	{
		upd(x*2,w+tg[x]);
		upd(x*2+1,w+tg[x]);
		tg[x]=0;
		ts[x]=ts[x*2]+ts[x*2+1];
	}
	else
	{
		Update(x,w);
	}
}
void Push(ll x)
{
	if(tg[x])
	{
		Update(x*2,tg[x]);
		Update(x*2+1,tg[x]);
		tg[x]=0;
	}
}
void Add(ll x,ll l,ll r,ll y)
{
	if(l<=tl[x]&&tr[x]<=r)
	{
		upd(x,y);
		return;
	}
	Push(x);
	if(l<=(tl[x]+tr[x])/2)
	{
		Add(x*2,l,r,y);
	}
	if(r>(tl[x]+tr[x])/2)
	{
		Add(x*2+1,l,r,y);
	}
	ts[x]=ts[x*2]+ts[x*2+1];
}
void Add2(ll x,ll to,ll y)
{
	if(tl[x]==tr[x])
	{
		ts[x].ans.b=y;
		return;
	}
	Push(x);
	if(to<=(tl[x]+tr[x])/2)
	{
		Add2(x*2,to,y);
	}
	else
	{
		Add2(x*2+1,to,y);
	}
	Update2(x);
}
void Add3(ll x,ll to,ll y,ll z)
{
	if(tl[x]==tr[x])
	{
		ts[x].ans.k=y;
		ts[x].ans.b=z;
		return;
	}
	Push(x);
	if(to<=(tl[x]+tr[x])/2)
	{
		Add3(x*2,to,y,z);
	}
	else
	{
		Add3(x*2+1,to,y,z);
	}
	ts[x]=ts[x*2]+ts[x*2+1];
}
pair<ll,ll> Query(ll x,ll l,ll r)
{
	if(l<=tl[x]&&tr[x]<=r)
	{
		return make_pair(ts[x].ans.b,ts[x].id);
	}
	Push(x);
	if(r<=(tl[x]+tr[x])/2)
	{
		return Query(x*2,l,r);
	}
	if(l>(tl[x]+tr[x])/2)
	{
		return Query(x*2+1,l,r);
	}
	pair<ll,ll> res=Query(x*2,l,r),res2=Query(x*2+1,l,r);
	if(res.first>=res2.first)
	{
		return res;
	}
	else
	{
		return res2;
	}
}
int main()
{
	ll b=read(),c=read();
	for(ll i=1;i<=b;i++)
	{
		a[i][0]=read();
	}
	for(ll i=1;i<=b;i++)
	{
		a[i][1]=read();
	}
	Build(1,1,b);
	for(ll i=1;i<=c;i++)
	{
		ll d=read();
		if(d==1)
		{
			ll e=read();
			Add(1,1,b,e);
		}
		else if(d==2)
		{
			ll e=read(),f=read(),g=read();
			for(int j=1;j<=g;j++)
			{
				pair<ll,ll> now=Query(1,e,f);
				if(j==g)
				{
					cout<<now.first<<"\n";
					break;
				}
				hf[j][0]=now.first;
				hf[j][1]=now.second;
				Add2(1,now.second,-N);
			}
			for(int j=g-1;j>=1;j--)
			{
				Add2(1,hf[j][1],hf[j][0]);
			}
		}
		else
		{
			ll e=read(),f=read(),g=read();
			Add3(1,e,f,g);
		}
	}
	return 0;
}