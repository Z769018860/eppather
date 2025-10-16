#include<string.h>
#include<stdio.h>
#include<math.h>
#define l(x) (x<<1)
#define r(x) ((x<<1)|1)
#define LL long long
#define N 100010
#define INF 0x3f3f3f3f3f3f3f3fll

int n,m,i,s,t,x,y,l,lsum=1;
int head[N],v[N],z[N];
LL dis[N];

struct Edge{
	int t,next,l;
}e[N*8];

inline void Add(int s,int t,int l){
	e[lsum].t=t;	e[lsum].l=l;	e[lsum].next=head[s];	head[s]=lsum++;
}

int Abs(int x){return (x<0)?-x:x;}
int Min(int a,int b){return (a<b)?a:b;}
int Max(int a,int b){return (a>b)?a:b;}

int read(){
	int p=0,f=1;	char	c=getchar();
	while (c<48||c>57)	{if (c=='-')	f=-1;	c=getchar();}
	while (c>=48&&c<=57)	p=(p<<1)+(p<<3)+c-48,c=getchar();
	return p*f;
}

void Swap(int *a,int *b){int t=*a;	*a=*b;	*b=t;}

inline void SPFA(int s){
	int i=0,x=0,t=1,w=0;
	memset(dis,INF,sizeof(dis));
	v[s]=1;	dis[s]=0;	z[t]=s;
	while (w!=t){
		w=(w+1)%n;	x=z[w];	v[x]=0;
		if (dis[z[(w+1)%n]]>dis[z[t]])	Swap(&z[t],&z[(w+1)%n]);
		for (i=head[x];i;i=e[i].next)
			if (dis[e[i].t]>(LL)e[i].l+dis[x]){
				dis[e[i].t]=(LL)e[i].l+dis[x];
				if (!v[e[i].t]){
					t=(t+1)%n;	v[z[t]=e[i].t]=1;
					if (dis[z[(w+1)%n]]>dis[z[t]])	Swap(&z[t],&z[(w+1)%n]);
				}
			}
	}
}

int main(){
	#ifdef __Marvolo
	freopen("zht.in","r",stdin);
	freopen("zht.out","w",stdout);
	#endif
	n=read();	m=read();	s=read();	t=read();
	for (i=1;i<=m;i++){
		x=read();	y=read();	l=read();
		Add(x,y,l);	Add(y,x,l);
	}
	SPFA(s);
	printf("%lld\n",dis[t]);
	return 0;
}