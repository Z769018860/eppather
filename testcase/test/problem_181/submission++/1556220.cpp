#include <bits/stdc++.h>
typedef long long ll;
char bufr[1<<21],*p1(bufr),*p2(bufr);
inline char getChar(void){if(p1==p2)p2=(p1=bufr)+fread(bufr,1,1<<21,stdin);return p1==p2?EOF:*p1++;}
inline void read(int &x){int c(0);while(!isdigit(c))c=getChar();x=0;while(isdigit(c))x=x*10+(c-'0'),c=getChar();}
inline void read(ll &x){int c(0);while(!isdigit(c))c=getChar();x=0;while(isdigit(c))x=x*10+(c-'0'),c=getChar();}
char bufw[1<<21],tmpw[60];
int plong,pshort;
void flush(void){fwrite(bufw+1,1,plong,stdout),plong=0;}
void _wr(int n){if(plong>2096000)flush();do tmpw[++pshort]=n%10+'0';while(n/=10);while(pshort)bufw[++plong]=tmpw[pshort--];}
constexpr int N(1e6+5);
int ksm(int x,ll y,int p){int ans(1);for(;y;y>>=1,x=(ll)x*x%p)if(y&1)ans=(ll)ans*x%p;return ans;}
int crt(int M1,int r1,int phi1,int M2,int r2,int phi2)
{
	return ((ll(r2-r1)*ksm(M1,phi2-1,M2)%M2+M2)*M1+r1)%(M1*M2);
}
int pr[10],pc[10],pw[10],cnt;
int fac[10][N],ifac[10][N];
int work(int i,ll n)
{
	int ans(1);
	bool flg(false);
	for(;n;n/=pr[i])
	{
		ans=(ll)ans*fac[i][n%pw[i]]%pw[i];
		if(fac[i][pw[i]-1]!=1&&((n/pw[i])&1))
			flg^=1;
	}
	return flg?pw[i]-ans:ans;
}
int worki(int i,ll n)
{
	int ans(1);
	bool flg(false);
	for(;n;n/=pr[i])
	{
		ans=(ll)ans*ifac[i][n%pw[i]]%pw[i];
		if(fac[i][pw[i]-1]!=1&&((n/pw[i])&1))
			flg^=1;
	}
	return flg?pw[i]-ans:ans;
}
int work(int i,ll n,ll m)
{
	ll p(0);
	for(ll j(n/pr[i]);j;j/=pr[i])
		p+=j;
	for(ll j(m/pr[i]);j;j/=pr[i])
		p-=j;
	for(ll j((n-m)/pr[i]);j;j/=pr[i])
		p-=j;
	if(p>=pc[i])
		return 0;
	int ans((ll)work(i,n)*worki(i,m)%pw[i]*worki(i,n-m)%pw[i]);
	for(;p;--p)
		ans=(ll)ans*pr[i]%pw[i];
	return ans;
}
int main(void)
{
	int T,MOD;
	read(T),read(MOD);
	for(int i(2);(ll)i*i<=MOD;++i)
	if(MOD%i==0)
	{
		pr[cnt]=i,pw[cnt]=1;
		while(MOD%i==0)
			MOD/=i,++pc[cnt],pw[cnt]*=i;
		++cnt;
	}
	if(MOD!=1)
		pr[cnt]=MOD,pc[cnt]=1,pw[cnt]=MOD,++cnt;
	for(int i(0);i<cnt;++i)
	{
		static int val[N];
		val[0]=1;
		for(int j(1);j<pw[i];++j)
			val[j]=j%pr[i]?j:1;
		fac[i][0]=ifac[i][0]=1;
		for(int j(1);j<pw[i];++j)
			fac[i][j]=(ll)fac[i][j-1]*val[j]%pw[i];
		ifac[i][pw[i]-1]=ksm(fac[i][pw[i]-1],pw[i]-pw[i]/pr[i]-1,pw[i]);
		for(int j(pw[i]-1);j;--j)
			ifac[i][j-1]=(ll)ifac[i][j]*val[j]%pw[i];
	}
	for(ll n,m;T;--T)
	{
		read(n),read(m);
		int M0(1),r0(0),phi(1);
		for(int i(0);i<cnt;++i)
			r0=crt(M0,r0,phi,pw[i],work(i,n,m),pw[i]-pw[i]/pr[i]),M0*=pw[i],phi*=pw[i]-pw[i]/pr[i];
		_wr(r0),bufw[++plong]='\n';
	}
	flush();
	return 0;
}