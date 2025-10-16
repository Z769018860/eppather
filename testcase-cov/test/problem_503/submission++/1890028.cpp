#include<bits/stdc++.h>
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1 ++)
#define N 140005
using namespace std;
int n,q;
char s,buf[100000], *p1, *p2;
inline int read(){
	char ch;
	int x = 0,f=1;
	while ((ch = gc) < 45);
	if(ch=='-') f=-1,ch=gc;
	do x = x * 10 + ch - 48; while ((ch = gc) >= 48);
	return x*f;
}
struct BIT{
	int now,sum,dlt,c[2*N],a[N],b[N];
	void add(int x,int y){
		for(;x<=2*N;x+=x&(-x)) c[x]+=y;
	}
	void mdf(int x,int y,int z){
		if(x>y) swap(x,y);
		x+=N,y+=N;
		add(x,z);
		add(y+1,-z);
	}
	int qry(int x){
		int res=0;x+=N;
		for(;x;x-=x&(-x)) res+=c[x];
		return res;
	}
	int check(int x,int y){
		return (x<0)^(y<0);
	}
	void init(){
		b[0]=1;now=1;dlt=sum=0;
		for(int i=1;i<=n;i++){
			b[i]=b[i-1]+a[i];
			if(i>1) mdf(b[i-1],b[i],1);
		}
		sum+=check(b[0],b[1]);
	}
	void right(){
		if(now==n) return;
		now++;
		b[now]=b[now-1]+a[now];
		mdf(b[now-1]-dlt,b[now]-dlt,-1);
		sum+=check(b[now-1],b[now]);
	}
	void left(){
		if(now==1) return;
		now--;
		mdf(b[now]-dlt,b[now+1]-dlt,1);
		sum-=check(b[now],b[now+1]);
	}
	void modify(){
		int x=read();
		sum-=check(b[now-1],b[now]);
		dlt=dlt-a[now]+x;
		a[now]=x;
		b[now]=b[now-1]+x;
		sum+=check(b[now-1],b[now]);
	}
	int query(){
		return sum+qry(-dlt);
	}
}X,Y;
int main(){
	n=read();
	for(int i=1;i<=n;i++) X.a[i]=read(),Y.a[i]=read();
	X.init();Y.init();
	q=read();
	while(q--){
		while ((s = gc) < 48);
		if(s=='F') X.right(),Y.right();
		if(s=='B') X.left(),Y.left();
		if(s=='Q') printf("%d\n",X.query()+Y.query());
		if(s=='C') X.modify(),Y.modify();
	}
}