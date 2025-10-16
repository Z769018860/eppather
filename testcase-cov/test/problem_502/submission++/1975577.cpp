#include <cstdio>
#include <unordered_map>
#include <random>
#define L 40
#define N 2000010
#define ull unsigned long long
int n,m; std::unordered_map<ull,int> inv;
ull man[N],msg[N],top;
std::mt19937_64 rng(0xdeadbeef);
ull get() {return rng()%top;}
ull add(ull x,ull y)
{
	ull tot=0,tmp=1;
	for(int i=0;i<L;i++)
	{
		tot+=(x%3+y%3)%3*tmp;
		x/=3, y/=3, tmp*=3;
	}
	return tot;
}
int read()
{
	int x=0,flag=1; char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar())
		if(ch=='-') flag=-1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return x*flag;
}
void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
int main()
{
	n=read(), m=read();
	top=1; for(int i=0;i<L;i++) top*=3;
	for(int i=1;i<=n;i++)
	{
		man[i]=get(); inv[man[i]]=i;
		inv[add(man[i],man[i])]=i;
	}
	for(int i=1,last=0,u,p;i<=m;i++)
	{
		u=read()^last, p=read()^last;
		msg[i]=add(msg[p],man[u]); int ans;
		if(!msg[i]) ans=-1;
		else if(!inv.count(msg[i])) ans=-2;
		else ans=inv[msg[i]];
		write(last=ans); putchar('\n');
	}
}