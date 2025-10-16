#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T f=0,x=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	inline int qpow(int x,int y){
		int ret=1;
		while(y){
			if(y&1) ret*=x;
			x*=x,y>>=1;
		}
		return ret;
	}
	inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
	inline int get(int p,int a,int k){
		if(!a) return 1;
		int phi=qpow(p,a-1)*(p-1);
		if(p==2 && a>2 && k%2==0) phi/=2;
		return phi/gcd(phi,k);
	}
	inline int calc(int p,int a,int k){
		int ret=0;
		for(int i=0;i*k<a;i++)
			ret+=get(p,a-i*k,k);
	
		return ret+1;
	}
	int p,n;
	int main(){
		p=read<int>(),read<int>(),n=read<int>();

		int ans=1;
		for(int i=2;i*i<=n;i++){
			int a=0;
			while(n%i==0) n/=i,a++;
			if(a) ans*=calc(i,a,p);
		}
		if(n!=1) ans*=calc(n,1,p);
		printf("%d\n",ans);
		return 0;
	}
}
int main(){
#ifdef my
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	return run::main();
}