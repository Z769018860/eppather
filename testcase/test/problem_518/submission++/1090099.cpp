#include<bits/stdc++.h>
#define N 500005
#define mp make_pair
#define int long long
using namespace std;
const int mod=19260817;
int n,m,len[N],tot2,ans;
int sum1[N],sum2[N],TOT[N],tot,S;
vector<int>p[N];
map<int,int>M;
map<pair<int,int>,int>M2;
set<int>st[N*5];
set<int>::iterator it,it2;
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int Ksm(int a,int n,int ans=1) {
	for(; n; n>>=1,a=a*a%mod)if(n&1)ans=ans*a%mod;
	return ans;
}
int G(int x) {
	if(M.find(x)==M.end())sum1[M[x]=++tot]=S;
	return M[x];
}
int G2(int x,int y) {
	if(M2.find(mp(x,y))==M2.end()) {
		st[M2[mp(x,y)]=++tot2].insert(0),st[tot2].insert(len[y]+1);
		sum2[tot2]=(len[y]*(len[y]+1)>>1)%mod;
	}
	return M2[mp(x,y)];
}
void Insert(int c,int x,int i) {
	ans-=S-((!TOT[c])?sum1[c]:0);
	if(!sum2[x])--TOT[c];
	else sum1[c]=sum1[c]*Ksm(sum2[x],mod-2)%mod;
	it=st[x].lower_bound(i),it2=--it,++it;
	sum2[x]=(sum2[x]-((*it-*it2)*(*it-*it2-1)>>1))%mod;
	sum2[x]=(sum2[x]+((i-*it2)*(i-*it2-1)>>1))%mod;
	sum2[x]=(sum2[x]+((*it-i)*(*it-i-1)>>1)+mod)%mod;
	if(!sum2[x])++TOT[c];
	else sum1[c]=sum1[c]*sum2[x]%mod;
	ans+=S-((!TOT[c])?sum1[c]:0),st[x].insert(i);
}
void Delete(int c,int x,int i) {
	ans-=S-((!TOT[c])?sum1[c]:0);
	if(!sum2[x])--TOT[c];
	else sum1[c]=sum1[c]*Ksm(sum2[x],mod-2)%mod;
	st[x].erase(i),it=st[x].lower_bound(i),it2=--it,++it;
	sum2[x]=(sum2[x]-((i-*it2)*(i-*it2-1)>>1))%mod;
	sum2[x]=(sum2[x]-((*it-i)*(*it-i-1)>>1))%mod;
	sum2[x]=(sum2[x]+((*it-*it2)*(*it-*it2-1)>>1)+mod+mod)%mod;
	if(!sum2[x])++TOT[c];
	else sum1[c]=sum1[c]*sum2[x]%mod;
	ans+=S-((!TOT[c])?sum1[c]:0);
}
signed main() {
	n=read(),m=read(),S=1;
	for(int i=1; i<=n; ++i)len[i]=read(),S=(len[i]*(len[i]+1)>>1)%mod*S%mod,p[i].resize(len[i]+2);
	for(int i=1; i<=n; ++i)for(int j=1; j<=len[i]; ++j)p[i][j]=read();
	for(int i=1; i<=n; ++i)for(int j=1; j<=len[i]; ++j)Insert(G(p[i][j]),G2(p[i][j],i),j);
	ans=(ans%mod+mod)%mod,cout<<ans<<"\n";
	for(int i=1,x,y,z; i<=m; ++i) {
		x=read(),y=read(),z=read();
		Delete(G(p[x][y]),G2(p[x][y],x),y),p[x][y]=z;
		Insert(G(p[x][y]),G2(p[x][y],x),y);
		ans=(ans%mod+mod)%mod,cout<<ans<<"\n";
	}
	return 0;
}