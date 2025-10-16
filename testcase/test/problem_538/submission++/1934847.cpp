#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
const ll oo=200000000000000ll;
const ll V=9000000000000000000ll;
ll m,s[N],q,a[N],k;
ll pos1,pos2,L; 
ll mnpos,mnv,mxpos,mxv;
inline void read(ll &x)
{
	ll f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
}
inline ll mn(ll _x,ll _y){return _x<_y?_x:_y;}
inline ll mx(ll _x,ll _y){return _x>_y?_x:_y;}
inline ll ab(ll _x){return _x<0?-_x:_x;}

inline void Solve(){
	if(pos1==1) printf("%lld %lld\n",s[pos2],s[pos2]);
	else if(pos2==-1) printf("%lld %lld\n",s[pos1],s[pos1]);
	else if(a[0]==a[1]) printf("%lld %lld\n",s[1],s[1]);
	else{
		if(a[s[pos1]&1]>a[s[pos2]&1]) printf("%lld %lld\n",s[pos1],s[pos2]);
		else printf("%lld %lld\n",s[pos2],s[pos1]);
	}
	return ;
}
int main()
{
	read(m);
	for(int i=1;i<=m;i++) read(s[i]);
	pos1=pos2=-1;
	for(int i=1;i<=m;i++){
		if(s[i]&1) pos1=(pos1==-1?s[i]:pos1);
		if(!((s[i]&1))) pos2=(pos2==-1?s[i]:pos2);
	}
	read(q);
	while(q--){
		read(a[0]);read(a[1]);read(k);
		if(k==0) {Solve();continue;}
		if(a[0]==a[1]&&a[0]==0){
			printf("%lld %lld\n",s[1],s[1]);
			continue;
		}
		L=2;while(233){
			a[L]=1ll*a[L-1]*k+a[L-2];
			if(a[L]>oo) break;
			if(a[L]<-oo) break;
			++L;
		}
		
		mnv=V;mnpos=0;
		mxv=-V;mxpos=0;
		for(int i=1;i<=m;i++){
			if(s[i]<=L){
				if(a[s[i]]<mnv){
					mnv=a[s[i]];mnpos=s[i];
				}
				if(a[s[i]]>mxv){
					mxv=a[s[i]];mxpos=s[i];
				}
			}
			else break;
		}
		
		
		if(s[m]>L){
			if(a[L]>a[L-1]&&a[L-1]>a[L-2]) mxpos=s[m];
			if(a[L]<a[L-1]&&a[L-1]<a[L-2]) mnpos=s[m];
		}
		if(!mnpos) mnpos=s[1];
		if(!mxpos) mxpos=s[1]; 
		
		printf("%lld %lld\n",mxpos,mnpos);
	}
	return 0;
}

