#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int Mxdt=100000;	
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline char pc(char ch,bool bj){
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
inline unsigned long long read()
{
	unsigned long long res=0,bj=0;char ch=gc();
	while(ch<'0'||ch>'9')bj|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return bj?-res:res;
}
void print(int x)
{
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,char ch)
{
	if(x<0)pc('-',false),x=-x;
	print(x),pc(ch,false);
}
int T,ans,tmp;unsigned long long k,now;
int solve(long long a,long long b){
	if(a>=b)return 0;
	int tmp=0;while(a<b){a*=3;tmp+=4;}
	return tmp;
}
int main(){



	T=read()+1;
	while(--T){
		k=read();now=1;tmp=0;ans=1e9;
		if(k<=5){cout<<(k+1)*2<<"\n";continue;}
		while(now<=k){
			ans=min(ans,tmp+solve(now,k));
			ans=min(ans,tmp+3+solve(now*2,k));
			ans=min(ans,tmp+6+solve(now*5,k));
			ans=min(ans,tmp+9+solve(now*2*5,k));
			now<<=2;tmp+=5;
		}
		ans=min(ans,tmp);
		cout<<(ans<<1)<<"\n";

	}

} 