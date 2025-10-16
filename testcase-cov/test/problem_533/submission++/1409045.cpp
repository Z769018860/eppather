#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
typedef long long ll;
ll read()
{
	ll f=1,x=0;int c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();
	return f*x;
}
ll max(ll a,ll b){return a>b?a:b;}
ll min(ll a,ll b){return a<b?a:b;}
ll abs(ll x){return x>0?x:-x;}
template<typename T> inline bool umin(T& a,T t){if(t<a)return a=t,1;return 0;}
template<typename T> inline bool umax(T& a,T t){if(t>a)return a=t,1;return 0;}

const int MAXN = 500011;
ll f[MAXN];
int main()
{
	f[0]=1;
	for(int i=1;i<=157;++i)
	{
		for(int j=0;j<i;++j)umax(f[i],f[j]*(i-j-1));
	}
	int task=read();
	while(task--)
	{
		printf("%d\n",int(std::lower_bound(f,f+151,read())-f)<<1);
	}
	return 0;
}