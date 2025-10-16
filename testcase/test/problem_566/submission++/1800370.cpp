#include<cstdio>
#include<algorithm>
typedef long long i64;
int n,m,i;
struct ask{
	int l,r;i64 d;
}a[500086];
int d[200086];
int gd(int g){
	if(d[g]==g)return g;
	return d[g]=gd(d[g]);
}bool cmp(ask a,ask b){
	return a.d<b.d;
}
i64 ans;
int check(i64 ad,int c){
	ans=0;int u=0,v=m-1,gu=0;
	for(i=0;i<n;++i)d[i]=i;
	while(c--){
		while(gd(a[u].l)==gd(a[u].r))++u;
		while(gd(a[v].l)==gd(a[v].r))--v;
		if(ad-a[u].d<a[v].d)d[gd(a[v].l)]=gd(a[v].r),ans+=a[v--].d;
		else d[gd(a[u].l)]=gd(a[u].r),ans+=ad-a[u++].d,++gu;
	}return gu;
}i64 splix(int c){
	i64 l=0,r=a[m-1].d<<1,m;
	while(l+1!=r){
		m=(l+r)>>1;
		if(check(m,c<<1)>c)r=m;
		else l=m;
	}check(l,c<<1);
	return ans-l*c;
}int main(){
	scanf("%d%d",&n,&m);
	for(i=0;i<m;++i){
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].d);
		--a[i].l,--a[i].r;a[i].d<<=1;
	}std::sort(a,a+m,cmp);
	printf("%llu\n",splix((n-1)>>1)>>1);
	return 0;
}