#include <bits/stdc++.h>

int F(int p,int m,int a)
{
	int Res=1;
	for(int i=1,t=1;i<=m;++i,t*=p)if((m-i)%a==0)
		Res+=p==2?a&1?t:(t-1)/2/(a&-a)+1:(p-1)*t/std::__gcd((p-1)*t,a);
	return Res;
}

int a,n,Ans=1;

int main()
{
	scanf("%d%*d%d",&a,&n);
	for(int i=2,k;1ll*i*i<=n;++i)
		if(n%i==0)
		{
			for(k=0;n%i==0;n/=i)++k;
			Ans*=F(i,k,a);
		}
	if(n!=1)Ans*=F(n,1,a);
	return printf("%d\n",Ans),0;
}