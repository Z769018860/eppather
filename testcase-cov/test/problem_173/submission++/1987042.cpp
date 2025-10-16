#include<bits/stdc++.h>
#define ri register int
#define F first
#define S second
using namespace std;
inline int rd(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int N=1000005,p=1000000007,bs=29;
int n,m,fc[N],hs[N],ly[N];char s[N];
int gt(int x,int y){return (hs[y]-1ll*hs[x-1]*fc[y-x+1]%p+p)%p;}
int gr(int x,int y){
	ri l=0,r=n-max(x,y)+1;
	while(l<r){
		ri md=l+r+1>>1;
		if(gt(x,x+md-1)==gt(y,y+md-1))l=md;
		else r=md-1;
	}
	return l;
}
int gl(int x,int y){
	ri l=0,r=min(x,y);
	while(l<r){
		ri md=l+r+1>>1;
		if(gt(x-md+1,x)==gt(y-md+1,y))l=md;
		else r=md-1;
	}
	return l;
}
struct run{int l,r,p;};vector<run>vc;
bool cmp(run u,run v){return u.l==v.l?u.r<v.r:u.l<v.l;}
bool operator==(run u,run v){return u.l==v.l&&u.r==v.r;}
bool cm(int x,int y){ri o=gr(x,y);return s[x+o]<s[y+o];}
stack<pair<int,int> >st;
void sol(int x){
	while(st.size())st.pop();st.push({n,n});ly[n]=n;
	for(ri i=n-1;i;--i){
		ri o=i;while(st.size()&&cm(i,st.top().F)!=x)o=st.top().second,st.pop();
		st.push({i,ly[i]=o});
	}
	for(ri i=1;i<=n;++i){
		ri j=ly[i],u=i,v=j;if(i!=1)u-=gl(i-1,j);if(j!=n)v+=gr(i,j+1);
		if(v-u+1>=2*(j-i+1))vc.push_back({u,v,j-i+1});
	}
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	for(ri i=fc[0]=1;i<=n;++i){fc[i]=1ll*fc[i-1]*bs%p;hs[i]=(1ll*hs[i-1]*bs+s[i]-'a'+1)%p;}
	for(ri i=0;i<2;++i)sol(i);
	sort(vc.begin(),vc.end(),cmp);
	vc.erase(unique(vc.begin(),vc.end()),vc.end());
	printf("%d\n",vc.size());
	for(auto i:vc)printf("%d %d %d\n",i.l,i.r,i.p);
	return 0;
}