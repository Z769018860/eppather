#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(LL x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const LL MOD=1e9+7;
inline LL Add(LL u,LL v){return u+v>=MOD?u+v-MOD:u+v;}
inline LL Sub(LL u,LL v){return u-v>=0?u-v:u-v+MOD;}
inline LL Mul(LL u,LL v){return LL(u)*LL(v)%MOD;}
inline LL add(LL &u,LL v){return u=Add(u,v);}
inline LL sub(LL &u,LL v){return u=Sub(u,v);}
inline LL mul(LL &u,LL v){return u=Mul(u,v);}
LL QuickPow(LL x,LL p=MOD-2)
{
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	mul(ans,base);
		mul(base,base);
		p>>=1;
	}
	return ans;
}
LL vis[1000005];
LL f[1000005];
LL A,B,C;
LL c1[1000005],c2[1000005];
int main(){
	A=read(),B=read(),C=read();
	f[0]=read()%C;
	LL d;
	LL r=0;
	for(d=1;;++d)
	{
		f[d]=(LL(A)*f[d-1]+B)%C+1;
		if(vis[f[d]])
		{
			r=vis[f[d]]-1;
			--d;
			break;
		}
		vis[f[d]]=d;
	}
	LL len=d-r;
	LL l=r+1;
	r=d;
	LL l1=read(),r1=read(),l2=read(),r2=read();
	while(l1<=min(l-1,r1))	++c1[f[l1]],++l1;
	while(l2<=min(l-1,r2))	++c2[f[l2]],++l2;
	for(LL i=l;i<=r;++i)
	{
		if(i<=r1)	c1[f[i]]=((r1-i)/len-(l1-i+len-1)/len+1)%MOD;
		if(i<=r2)	c2[f[i]]=((r2-i)/len-(l2-i+len-1)/len+1)%MOD;
	}
	for(LL i=1;i<=C;++i)	add(c1[i],c1[i-1]),add(c2[i],c2[i-1]);
	LL ans=0;
	for(LL i=1;i<=C;++i)
	{
		for(LL j=2;;++j)
		{
			LL R=max(i+1,LL((j+sqrt(LL(j)*j-4))/2*i+1));
			if(R>C)	break;
			LL p=Sub(c1[i],c1[i-1]),q=Sub(c2[i],c2[i-1]);
			add(ans,Add(Mul(p,Sub(c2[C],c2[R-1])),Mul(q,Sub(c1[C],c1[R-1]))));
		}
	}
	add(ans,Mul(2,Mul(c1[C],c2[C])));
	write(ans),puts("");
	return 0;
}