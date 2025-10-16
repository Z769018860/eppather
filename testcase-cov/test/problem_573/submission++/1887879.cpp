







#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<cmath>
#include<complex>
#include<queue>
#include<deque>
#include<map>
#include<set>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define Rep(i,x,y) for(int i=(int)(x);i<=(int)(y);i++)
#define Per(i,x,y) for(int i=(int)(x);i>=(int)(y);i--)
#define DEBUG 1
namespace FastIO{
#define isdigit(x) (x>='0'&&x<='9')
#define MAXSIZE (1<<20)
	char buf[MAXSIZE],pbuf[MAXSIZE],*pp=pbuf,*p1,*p2;
#if DEBUG
#else
	IO():p1(buf),p2(buf),pp(pbuf){}
	~IO(){fwrite(pbuf,1,pp-pbuf,stdout);}
#endif
	inline char gc(){
#if DEBUG
		return getchar();
#endif
		if(p1==p2)p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
		return p1==p2?' ':*p1++;
	}
	template<typename T>
	inline void read(T &x) {
		double tmp=1;
		bool sign=0;x=0;
		char c=gc();
		for(;!isdigit(c);c=gc())if(c=='-')sign=1;
		for(;isdigit(c);c=gc())x=x*10+(c-'0');
		if(c=='.')for(c= gc();isdigit(c);c=gc())tmp/=10.0,x+=tmp*(c-'0');
		if(sign)x=-x;
	}inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(char *s){
		char c=gc();
		for(;blank(c);c=gc());
		for(;blank(c);c=gc())*s++=c;
		*s=0;
	}inline void read(char &c){for(c=gc();blank(c);c=gc());}
	template<typename T,typename...Args>
	inline void read(T&x,Args&...args){read(x);read(args...);}
	inline void pc(const char &c) {
#if DEBUG
		putchar(c);
#else
		if(pp-pbuf==MAXSIZE)fwrite(pbuf,1,MAXSIZE,stdout),pp=pbuf;
		*pp++=c;
#endif
	}template<typename T>
	inline void write(T x){
		if(x<0)x=-x,pc('-');
		static int sta[35];
		int top=0;
		do{sta[top++]=x%10,x/=10;}while(x);
		while(top)pc(sta[--top]+'0');
	}template<typename T>
	inline void write(T x,char lastChar){write(x);pc(lastChar);}
}
using namespace FastIO;
const int N=1e6+5;
const int MOD=998244353;
struct matrix{
	int x,y;
	ll a[5][5];
	matrix(){}
	matrix(int p,int q){
		x=p;y=q;
		memset(a,0,sizeof a);
	}
};
matrix mul(matrix p,matrix q){
	matrix r(p.x,q.y);
	int i,j,k;
	for(i=0;i<p.x;i++)for(j=0;j<q.y;j++)for(k=0;k<p.y;k++)r.a[i][j]=(r.a[i][j]+p.a[i][k]*q.a[k][j]%MOD)%MOD;
	return r;
}
void fz(matrix &p,matrix q){
	p.x=q.x;p.y=q.y;
	int i,j;
	for(i=0;i<q.x;i++)for(j=0;j<q.y;j++)p.a[i][j]=q.a[i][j];
}
matrix get_mat(int x){
	matrix r(2,2);
	r.a[0][0]=x;r.a[0][1]=r.a[1][0]=1;
	return r;
}
matrix get_inv(int x){
	matrix r(2,2);
	r.a[1][1]=MOD-x;r.a[0][1]=r.a[1][0]=1;
	return r;
}
matrix danwei(){
	matrix r(2,2);
	r.a[0][0]=r.a[1][1]=1;
	return r;
}
int n;
matrix mts[N],ivs[N];
signed main(){
	int m,type,x,y,op,lans=0;
	matrix res;
	fz(mts[0],danwei());
	fz(ivs[0],danwei());
	read(n,m,type);
	Rep(i,1,n){
		read(x);
		fz(mts[i],mul(mts[i-1],get_mat(x)));
		fz(ivs[i],mul(get_inv(x),ivs[i-1]));
	}
	while(m--){
		read(op);
		if(op==1){
			read(x);if(type)x^=lans;n++;
			fz(mts[n],mul(mts[n-1],get_mat(x)));
			fz(ivs[n],mul(get_inv(x),ivs[n-1]));
		}else{
			read(x,y);if(type)x^=lans,y^=lans;
			res.x=res.y=2;res.a[0][0]=1;res.a[0][1]=res.a[1][0]=res.a[1][1]=0;
			fz(res,mul(mul(ivs[x-1],mts[y]),res));
			write(res.a[0][0],' ');
			write(res.a[1][0],'\n');
			lans=res.a[0][0]^res.a[1][0];
		}
	}
	return 0;
}