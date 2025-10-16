#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

#define mod 1062127643
#define maxn 2000005
#define Base 131
#define ll long long
int n;
char s[maxn];
ll pw[maxn],hsh[maxn];
void prehsh(char*s,int n){
	pw[0]=1;
	For(i,1,n)
		pw[i]=pw[i-1]*Base%mod,
		hsh[i]=(hsh[i-1]*Base+s[i]-'a'+1)%mod;
}
inline int H(int l,int r){
	ll res=hsh[r]-hsh[l-1]*pw[r-l+1]%mod;
	return res>=0?res:res+mod;
}







bool eql(int l,int r,int len)
{return ((hsh[l]-hsh[l-len]*pw[len])-(hsh[r]-hsh[r-len]*pw[len]))%mod==0;}
bool eqr(int l,int r,int len)
{return ((hsh[l+len-1]-hsh[l-1]*pw[len])-(hsh[r+len-1]-hsh[r-1]*pw[len]))%mod==0;}


inline int lcs(int u,int v)
{
	int l=0,r=min(u,v);
	if(u==v)return r;
	if(r<=20||!eql(u,v,20)){
		int res=0;
		while(s[u-res]==s[v-res])++res;
		return res;
	}
	while(l<r){
		int mid=(l+r+1)>>1;
		if(eql(u,v,mid))l=mid;
		else r=mid-1;
	}
	return l;
}
inline int lcp(int u,int v)
{
	int l=0,r=n-max(u,v)+1;
	if(u==v)return r;
	if(r<=20||!eqr(u,v,20)){
		int res=0;
		while(s[u+res]==s[v+res])++res;
		return res;
	}
	while(l<r){
		int mid=(l+r+1)>>1;
		if(eqr(u,v,mid))l=mid;
		else r=mid-1;
	}
	return l;
}

struct runs{
	int l,r,p;
	bool operator <(const runs&b)const{
		if(l!=b.l)return l<b.l;
		if(r!=b.l)return r<b.r;
		return p<b.p;
	}
	bool operator ==(const runs&b)const{return l==b.l&&r==b.r&&p==b.p;}
}b[maxn<<1];
int cnt;
inline void chk(int u,int v){
	int tl=lcs(u,v),tr=lcp(u,v);
	if(tl+tr>=v-u+1) b[++cnt]=(runs){u-tl+1,v+tr-1,v-u};
}
inline bool cmpsuf(int u,int v){
	int x=lcp(u,v);
	return s[u+x]<s[v+x];
}

int st[maxn],top,lyn[maxn];
void zhouAK(bool o)
{
	lyn[n]=n;
	st[0]=n+1,st[top=1]=n;
	Rep(i,n-1,1){
		while(top&&cmpsuf(i,st[top])==o)--top;
		st[++top]=i,lyn[i]=st[top-1]-1;
	}
}

signed main()
{

	scanf("%s",s+1),n=strlen(s+1);
	prehsh(s,n);
	zhouAK(0); For(i,1,n-1)chk(i,lyn[i]+1);
	zhouAK(1); For(i,1,n-1)chk(i,lyn[i]+1);
	sort(b+1,b+cnt+1),cnt=unique(b+1,b+cnt+1)-b-1;
	cout<<cnt<<endl;
	For(i,1,cnt)printf("%d %d %d\n",b[i].l,b[i].r,b[i].p); 
    return 0;
}
