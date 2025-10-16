#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int T,mod;
inline int M(int x){return (x>=mod)?(x-mod):x;}
inline int M1(int x){return (x<0)?(x+mod):x;}
inline int ksm(int p,int k){int res=1;while(k){if(k&1)res=1ll*res*p%mod;k>>=1;p=1ll*p*p%mod;}return res;}
inline int sol(int a)
{
	if(mod%3!=1)return ksm(a,(1ll*(3-(mod-1)%3)*(mod-1)+1)/3);if(ksm(a,(mod-1)/3)!=1)return 0;
	int t=(mod-1)/3,pt=t,z=1,y,o,b=1;while(pt%3==0)pt/=3;while(ksm(z,t)==1)z=1ll*rand()*rand()%(mod-1)+1;
	while(t%3==0)
	{
		int r=ksm(a,t/3);if(r==1)goto Ou;y=ksm(z,(mod-1)/(3*t));o=ksm(y,t);while(1ll*o*r%mod!=1)o=1ll*o*o%mod,y=1ll*y*y%mod;
		a=1ll*a*y%mod*y%mod*y%mod;b=1ll*b*y%mod;
		Ou:t/=3;
	}
	return 1ll*ksm(a,(1ll*(3-(t%3))*t+1)/3)*ksm(b,mod-2)%mod;
}
int main(){
	srand(19260817);
	scanf("%d",&T);int a;
	while(T--){scanf("%d%d",&a,&mod);printf("%d\n",sol(a));}return 0;
}