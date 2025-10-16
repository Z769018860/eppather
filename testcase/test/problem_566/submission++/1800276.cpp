#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read() {
	char ch=getchar();int res=0,fl=1;
	while(ch<'0'||ch>'9'){if(ch=='-') fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){res=res*10+ch-'0';ch=getchar();}
	return res*fl;
}
const int M=500050;
const int N=200005;
const int inf=1000000005;
struct edge{
	int u,v,w;
}e1[M],e2[M];
bool operator <(edge A,edge B) {return A.w>B.w;}
int n,m,need,K,cnt;
ll ans;
int fa[N];
int get_fa(int x) {return (fa[x]==x)?x:fa[x]=get_fa(fa[x]);}
int merge(int x,int y) {
	x=get_fa(x);y=get_fa(y);
	if(x==y) return 0;
	fa[x]=y;
	return 1;
}
void inital() {for(int i=1;i<=n;++i) fa[i]=i;return ;}
void calc(int mid) {

	ans=0;K=0;cnt=n;
	inital();
	for(int s1=1,s2=1;(s1<=m||s2<=m)&&((n&1)||cnt>2);) {
		if(s1>m||(s2<=m&&e2[s2].w>e1[s1].w-mid)) {
			if(merge(e2[s2].u,e2[s2].v)) {
				ans+=e2[s2].w;
				cnt--;
			}
			s2++;
		}
		else {
			if(merge(e1[s1].u,e1[s1].v)) {
				ans+=e1[s1].w-mid;
				K++;
				cnt--;
			}
			s1++;
		}
	}


	return ;
}
int main() 
{


	n=read();m=read();need=(n-1)/2;
	for(int i=1;i<=m;++i) {
		int x=read(),y=read(),z=read();
		e1[i]=(edge){x,y,z};
		e2[i]=(edge){x,y,-z};
	}
	sort(e1+1,e1+1+m);
	sort(e2+1,e2+1+m);
	int l=-inf,r=inf;
	while(l<r) {
		int mid=l+((r-l+1)>>1);

		calc(mid);
		if(K>=need) l=mid;
		else r=mid-1;
	}
	calc(l);
	ll Ans=ans+1ll*l*need;
	printf("%lld",Ans);

	return 0;
}
