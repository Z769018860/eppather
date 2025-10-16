#include<bits/stdc++.h>
using namespace std;
long long ans2[300100];
int n,q,deg[300010],ans1[300010],a[300010],st[300010],le2[300010],le[300010],b[300100],L[300100],R[300010];
vector<int> e[300010];
inline void getl(){
	int cnt=0;
	auto mdy=[&](int x,int l,int r){
		cnt-=b[x]?0:deg[x];
		b[x]=L[x]<l || R[x]>r;deg[x]^=1;
		cnt+=b[x]?0:deg[x];
	};
	for(int i=1,j=1;i<=n;++i){
		b[i]=1;
		for(int x:e[i])if(j<=x && x<=i)deg[i]^=1,mdy(x,j,i);
		for(;cnt;){
			++j;
			for(int x:e[j-1])if(j<=x && x<=i)deg[j-1]^=1,mdy(x,j,i);
		}
		le[i]=j;
	}
	le2[1]=1;for(int i=2;i<=n;++i)le2[i]=i>2 && (a[i]>a[i-1])==(a[i-1]>a[i-2])?le2[i-1]:i-1;
}
int calc()
{
	if(n==1) return 1;
	bool fl1=1,fl2=1;
	for(int i=1;i<n;i++)
	{
		a[i]<a[i+1]?fl1=0:fl2=0;
	}
	if(fl1||fl2) return 2;
	for(int i=1;i<=n;i++)
	{
		if(!b[i]&&e[i].size()&1) return 4;
	}
	return 3;
}
void build()
{
	int w;
	for(int i=1;i<=n;i++) 
	{
		L[i]=300010;
	}
	w=0,st[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(;w&&a[st[w]]<a[i];w--);
		if(w)
		{
			e[st[w]].push_back(i);
			e[i].push_back(st[w]);
		}
		L[i]=min(L[i],st[w]);
		st[++w]=i;
	}
	for(int i=1;i<=w;i++)
	{
		b[st[i]]=1;
	}
	w=0,st[0]=n+1;
	for(int i=n;i;i--)
	{
		for(;w&&a[st[w]]<a[i];w--);
		if(w)
		{
			e[st[w]].push_back(i);
			e[i].push_back(st[w]);
		}
		R[i]=max(R[i],st[w]);
		st[++w]=i;
	}
	for(int i=1;i<=w;i++)
	{
		b[st[i]]=1;
	}
	w=0,st[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(;w&&a[st[w]]>a[i];w--);
		if(w)
		{
			e[st[w]].push_back(i);
			e[i].push_back(st[w]);
		}
		L[i]=min(L[i],st[w]);
		st[++w]=i;
	}
	for(int i=1;i<=w;i++)
	{
		b[st[i]]=1;
	}
	w=0,st[0]=n+1;
	for(int i=n;i;i--)
	{
		for(;w&&a[st[w]]>a[i];w--);
		if(w)
		{
			e[st[w]].push_back(i);
			e[i].push_back(st[w]);
		}
		R[i]=max(R[i],st[w]);
		st[++w]=i;
	}
	for(int i=1;i<=w;i++)
	{
		b[st[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end()); 
	}
	if(n>1)cout<<calc()<<endl;
}
vector<pair<int,int> > qu[300010],qu2[300010];
long long bi1[300010],bi2[300100];
void add(long long *b,int x,int v)
{
	x=n-x+1;
	while(x<=n)
	{
		b[x]+=v;
		x+=(x&(-x));
	}
}
long long sum(long long *b,int x)
{
	x=n-x+1;
	long long su=0;
	while(x){
		su+=b[x];
		x-=(x&(-x));
	}
	return su;
}
void slo(int *l,vector<pair<int,int> > *q)
{
	memset(bi1+1,0,n<<3),memset(bi2+1,0,n<<3);
	for(int i=1;i<=n;i++)
	{
		add(bi1,l[i],1);
		add(bi2,l[i],l[i]);
		for(auto u:q[i])
		{
			int j,k;
			tie(j,k)=u;
			ans2[k]=sum(bi2,j)-sum(bi1,j)*j;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
	}
	build();
	getl();
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		if(l==r) {
			ans1[i]=ans2[i]=1;
			continue;
		}
		if(l>=le[r])
		{
			if(l>=le2[r]) ans1[i]=2,ans2[i]=1ll*(r-l+1)*(r-l)>>1;
			else ans1[i]=3,qu2[r].push_back({l,i});
		}
		else ans1[i]=4,qu[r].push_back({l,i});
	}
	slo(le,qu);
	slo(le2,qu2);
	for(int i=1;i<=q;i++)
	{
		cout<<ans1[i]<<" "<<ans2[i]<<'\n';
	}
}