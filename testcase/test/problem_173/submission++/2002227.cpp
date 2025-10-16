#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
const int N=1e6+7,mod=1e9+21,B=31;
typedef long long ll;const ll Mod=mod;
struct Run{int l,r,p;};std::vector<Run> alrn;
bool operator<(Run x,Run y){return x.l==y.l?(x.r==y.r?x.p<y.p:x.r<y.r):x.l<y.l;}
char s[N];int h[N],pw[N],ly[N],stk[N],n;
inline int gvl(int l,int r){return (h[r]-(ll)h[l-1]*pw[r-l+1]%Mod+Mod)%Mod;}
int lcp(int x,int y)
{
	int l=0,r=std::min(x,y);
	while(l<r){int mid=(l+r+1)>>1;if(gvl(x-mid+1,x)==gvl(y-mid+1,y))l=mid;else r=mid-1;}
	return l;
}
int lcs(int x,int y)
{
	int l=0,r=n-std::max(x,y)+1;
	while(l<r){int mid=(l+r+1)>>1;if(gvl(x,x+mid-1)==gvl(y,y+mid-1))l=mid;else r=mid-1;}
	return l;
}
bool cmpsf(int x,int y){int z=lcs(x,y);return s[x+z]<s[y+z];}
void lyndon(bool op){int tp=0;*stk=n+1;for(int i=n;i;--i){while(tp&&cmpsf(i,stk[tp])==op)--tp;ly[i]=stk[tp];stk[++tp]=i;}}
void chk(int x,int y)
{
	if(y>n)return;
	int tp=lcp(x,y),ts=lcs(x,y);
	if(tp+ts>=y-x+1)alrn.push_back({x-tp+1,y+ts-1,y-x});
}
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	*pw=1;for(int i=1;i<=n;++i)pw[i]=(ll)pw[i-1]*B%Mod;
	for(int i=1;i<=n;++i)h[i]=((ll)h[i-1]*B+s[i]-'a'+1)%Mod;
	for(int op=0;op<2;++op){lyndon(op);for(int i=1;i<n;++i)chk(i,ly[i]);}
	std::sort(alrn.begin(),alrn.end());int cnt=0;for(int j=0;j<(int)alrn.size();++j)cnt+=(!j||alrn[j].l!=alrn[j-1].l||alrn[j].r!=alrn[j-1].r);
	printf("%d\n",cnt);for(int j=0;j<(int)alrn.size();++j)if(!j||alrn[j].l!=alrn[j-1].l||alrn[j].r!=alrn[j-1].r)printf("%d %d %d\n",alrn[j].l,alrn[j].r,alrn[j].p);
	return 0;
}