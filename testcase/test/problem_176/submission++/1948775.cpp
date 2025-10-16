#include<cstdio>
#include<queue>
#include<algorithm>
const int N=2e5+7;typedef long long ll;
struct lin{int k,id;ll b;};lin a[N],tr[N*4];ll lz[N*4],sn[N*4];
inline lin max(lin x,lin y){return x.b>y.b?x:y;}
ll dv(lin x,lin y){return x.k<=y.k?(ll)1e18:(y.b-x.b)/(x.k-y.k);}
inline void tadd(int x,ll v){tr[x].b+=tr[x].k*v;lz[x]+=v;sn[x]-=v;}
inline void push(int x){if(lz[x])tadd(x<<1,lz[x]),tadd(x<<1|1,lz[x]),lz[x]=0;}
void pull(int x)
{
	int ls=x<<1,rs=x<<1|1;
	if(tr[ls].b>=tr[rs].b)tr[x]=tr[ls],sn[x]=dv(tr[rs],tr[ls]);
	else tr[x]=tr[rs],sn[x]=dv(tr[ls],tr[rs]);
	sn[x]=std::min(sn[x],std::min(sn[ls],sn[rs]));
}
void chg(int p,int l,int r,int rt)
{
	if(l==r){tr[rt]=a[p];return;}
	int mid=(l+r)>>1;push(rt);
	if(p<=mid)chg(p,l,mid,rt<<1);
	else chg(p,mid+1,r,rt<<1|1);
	pull(rt);
}
void upd(int L,int R,ll v,int l,int r,int rt)
{
	if(L<=l&&r<=R&&v<=sn[rt])return tadd(rt,v);
	int mid=(l+r)>>1;push(rt);
	if(L<=mid)upd(L,R,v,l,mid,rt<<1);
	if(R>mid)upd(L,R,v,mid+1,r,rt<<1|1);
	pull(rt);
}
void build(int l,int r,int rt)
{
	if(l==r){sn[rt]=1e18;tr[rt]=a[l];return;}
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pull(rt);
}
lin qry(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)return tr[rt];
	int mid=(l+r)>>1;lin ans{0,0,-(ll)4e18};push(rt);
	if(L<=mid)ans=qry(L,R,l,mid,rt<<1);
	if(R>mid)ans=max(ans,qry(L,R,mid+1,r,rt<<1|1));
	return ans;
}
struct pii{int l,r;lin v;};
bool operator<(pii x,pii y){return x.v.b<y.v.b;}
int main()
{
	int n,q,o,l,r,x;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i].k),a[i].id=i;
	for(int i=1;i<=n;++i)scanf("%lld",&a[i].b);
	build(1,n,1);
	while(q--)
	{
		scanf("%d",&o);
		if(o==1)scanf("%d",&x),upd(1,n,x,1,n,1);
		else if(o==2)
		{
			scanf("%d%d%d",&l,&r,&x);
			std::priority_queue<pii> pq;
			pq.push({l,r,qry(l,r,1,n,1)});
			lin zz=qry(l,r,1,n,1);

			while(--x)
			{
				pii z=pq.top();pq.pop();int p=z.v.id;
				if(p!=z.l)pq.push({z.l,p-1,qry(z.l,p-1,1,n,1)});
				if(p!=z.r)pq.push({p+1,z.r,qry(p+1,z.r,1,n,1)});
			}
			printf("%lld\n",pq.top().v.b);
		}
		else scanf("%d",&x),scanf("%d%lld",&a[x].k,&a[x].b),chg(x,1,n,1);
	}
	return 0;
}