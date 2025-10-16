#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=23;
const int M=(1<<22)+5;
const int mod=1e9+7;
int n,m,k,x;
int t[M],ans[M];
inline void read(int &x) 
{
	int f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
} 
inline int mn(int _x,int _y){return _x<_y?_x:_y;}
inline int mx(int _x,int _y){return _x>_y?_x:_y;}
inline int ab(int _x){return _x<0?-_x:_x;}
inline int modadd(int x,int y){
	x+=y;return (x>=mod?x-mod:x);
}
inline int modsub(int x,int y){
	x-=y;return (x<0?x+mod:x);
}
inline int qpow(int base,int cnt){
	int rest=1;
	while(cnt){
		if(cnt&1) rest=1ll*rest*base%mod;
		base=1ll*base*base%mod;
		cnt>>=1;
	}
	return rest;
}
inline void FWTAND(int *A,int len,int type){
	if(type==1){
		for(int nL=2;nL<=len;nL<<=1){
			int o=(nL>>1);
			for(int i=0;i<len;i+=nL)
				for(int j=0;j<o;j++)
					A[i+j]=modadd(A[i+j],A[i+j+o]);
		}
	}
	else{
		for(int nL=2;nL<=len;nL<<=1){
			int o=(nL>>1);
			for(int i=0;i<len;i+=nL)
				for(int j=0;j<o;j++)
					A[i+j]=modsub(A[i+j],A[i+j+o]);
		}
	}
	return ;
}
int main()
{
	read(n);read(m);read(k);
	for(int i=1;i<=m;i++){
		read(x);++t[x];
	}
	FWTAND(t,(1<<n),1);
	for(int i=0;i<(1<<n);i++) 
		ans[i]=qpow(t[i],k);
	FWTAND(ans,(1<<n),-1);
	printf("%d\n",modsub(qpow(m,k),ans[0]));
	return 0;
}  