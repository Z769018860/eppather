#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
typedef long long ll;
int n,a[1000002];
ll tree[1000002],f[1000002],ans=0;
inline int read()
{
	int xr=0,F=1;char cr=getchar();
	while(cr<'0'||cr>'9') {if(cr=='-') F=-1;cr=getchar();}
	while(cr>='0'&&cr<='9')
	    xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
	return xr*F;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int lowbit(int x){return x&(-x);}
inline void add(int x,int d)
{
	while(x<=n)
	{
		tree[x]+=d;
		x+=lowbit(x);
	}
}
inline int sum(int x)
{
	int ret=0;
	while(x)
	{
		ret+=tree[x];
		x-=lowbit(x);
	}
	return ret;
}
int main() {
	n=read();
	f[0]=1;
	for(register int i=1;i<=n;i++) 
	{
		f[i]=f[i-1]*i%MOD;
		add(i,1);
	}
	for(register int i=1;i<=n;i++)
	{
		a[i]=read();
		add(a[i],-1);
		ans+=sum(a[i]-1)*f[n-i]%MOD;
	}
	ans%=MOD;
	write(++ans);
    return 0;
}