#include <iostream>
#include <algorithm>
constexpr int N(3e3+10),p(998244353);
int fp(int a,int b){int ans(1),off(a);while(b){if(b&1) ans=1ll*ans*off%p;off=1ll*off*off%p;b>>=1;}return ans;}
int main()
{
	static int d(0);
	static int g[N],f[N];g[0]=1;
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	int n;std::cin>>n;
	while(n--)
	{
		int tp,x,y;std::cin>>tp>>x;
		if(tp==1)
		{
			std::cin>>y;int v(p-x);
			int t(0),q(0);
			for(int j(d);j>=0;--j) t=(1ll*t*x+g[j])%p,q=(1ll*q*x+f[j])%p;
			int val(1ll*(y-q+p)*fp(t,p-2)%p);
			for(int j(0);j<=d;++j) f[j]=(f[j]+1ll*val*g[j])%p;
			for(int j(d);j>=0;--j) g[j+1]=(1ll*g[j+1]*v+g[j])%p;
			g[0]=1ll*g[0]*v%p;++d;
			
			
			
		}
		else
		{
			int ans(0);
			for(int j(d-1);j>=0;--j) ans=(1ll*ans*x+f[j])%p;
			std::cout<<ans<<"\n";
		}
	}
    return 0;
}