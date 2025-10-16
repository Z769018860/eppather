#include <bits/stdc++.h>
#define F first
#define S second
#define ll int
#define N 1200010
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
ll rint(){
	ll ret=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c-'0'),c=getchar();
	return ret;
}
ll n,m,k,a[N],b[N],va[N],vb[N],lsta[N],nxta[N],lstb[N],nxtb[N];
ll la,lb,sza,szb;
long long ans,curans=0;
map<ll,ll> mpa,mpb;
bool cmpa(ll x,ll y){return make_pair(x&(-x),x)>make_pair(y&(-y),y);}
bool cmpb(ll x,ll y){return make_pair(x&(-x),x)<make_pair(y&(-y),y);}
void erza(ll x)
{
	if(x<la)
	{
		sza--;
	}
	else
	{
		if(x==la)
		{
			la=nxta[la];
		}
		curans-=va[x];
	}
	if(lsta[x]>=0)
	{
		nxta[lsta[x]]=nxta[x];
	}
	if(nxta[x]<=n)
	{
		lsta[nxta[x]]=lsta[x];
	}
	return;
}
void erzb(ll x)
{
	if(x<lb)
	{
		szb--;
		curans-=vb[x];
	}
	else if(x==lb)
	{
		lb=nxtb[lb];
	}
	if(lstb[x]>=0)
	{
		nxtb[lstb[x]]=nxtb[x];
	}
	if(nxtb[x]<=m)
	{
		lstb[nxtb[x]]=lstb[x];
	}
	return;
}
void recalc()
{
	k--;
	while(sza>szb)
	{
		la=lsta[la];
		curans+=va[la];
		sza--;
	}
	while(szb>sza)
	{
		lb=lstb[lb];
		curans-=vb[lb];
		szb--;
	}
	while(sza>k)
	{
		la=lsta[la];
		lb=lstb[lb];
		curans+=va[la]-vb[lb];
		sza--,szb--;
	}
	while(sza<k&&va[la]>vb[lb])
	{
		curans+=vb[lb]-va[la];
		la=nxta[la];
		lb=nxtb[lb];
		sza++,szb++;
	}
	return;
}
int main(){
	ll i,j;
	n=rint();
	i=0;
	while(n--)
	{
		ll x=rint();
		if(x)
		{
			a[i++]=x;
			mpa[x]++;
		}
	}
	n=i;
	m=rint();
	i=0;
	while(m--)
	{
		ll x=rint();
		if(x)
		{
			b[i++]=x;
			mpb[x]++;
		}
	}
	m=i;
	k=min(min(n,m),rint());
	sort(a,a+n,cmpa);
	sort(b,b+m,cmpb);
	for(i=0;i<=n;i++)
	{
		va[i]=a[i]&(-a[i]);
		nxta[i]=i+1;
		lsta[i]=i-1;
	}
	for(i=0;i<=m;i++)
	{
		vb[i]=b[i]&(-b[i]);
		nxtb[i]=i+1;
		lstb[i]=i-1;
	}
	for(la=lb=sza=szb=0;sza<k;la=nxta[la],lb=nxtb[lb])
	{
		if(va[la]<=vb[lb])
		{
			break;
		}
		sza++,szb++;
		curans+=vb[lb];
	}
	for(i=la;i<n;i++)
	{
		curans+=va[i];
	}
	ans=curans;
	for(i=0,j=m-1;i<n&&k>0;i++)
	{
		if(!(mpa[a[i]]&&mpb[a[i]]))
		{
			continue;
		}
		for(;j>=0&&b[j]!=a[i];j=lstb[j]);
		ll nj=lstb[j];
		mpa[a[i]]--,mpb[a[i]]--;
		erza(i);
		erzb(j);
		recalc();
		j=nj;
		ans=min(ans,curans);
	}
	cout<<ans<<'\n';
	return 0;
}