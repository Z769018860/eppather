#include<bits/stdc++.h>



using namespace std;

#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define mt make_tuple
#define SZ(v) ((int)v.size())
#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...) 1064
#endif
template<typename T1,typename T2>void chkmin(T1 &x,T2 y){if(x>y)x=y;}
template<typename T1,typename T2>void chkmax(T1 &x,T2 y){if(x<y)x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long double ld;
#ifdef FASTIO
#define FILE_SIZE 1<<23
char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
#ifdef LOCAL
inline char getc(){return getchar();}
inline void putc(char c){putchar(c);}
#else
inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
inline void putc(char x){*p3++=x;}
#endif
template<typename T>void read(T &x){
	x=0;char c=getc();T neg=0;
	while(!isdigit(c))neg|=(c=='-'),c=getc();
	while(isdigit(c))x=x*10+(c-'0'),c=getc();
	if(neg)x=-x;
}
template<typename T>void recursive_print(T x){if(!x)return;recursive_print(x/10);putc(x%10^48);}
template<typename T>void print(T x){if(!x)putc('0');if(x<0)putc('-'),x=-x;recursive_print(x);}
template<typename T>void print(T x,char c){print(x);putc(c);}
void readstr(char *s){char c=getc();while(c<=32||c>=127)c=getc();while(c>32&&c<127)s[0]=c,s++,c=getc();(*s)=0;}
void printstr(string s){for(int i=0;i<s.size();i++)putc(s[i]);}
void printstr(char *s){int len=strlen(s);for(int i=0;i<len;i++)putc(s[i]);}
void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
#endif
const int MAXN=1e5;
int n,m,a[MAXN+5],ord[MAXN+5],blk_sz,blk_cnt,L[MAXN+5],R[MAXN+5],bel[MAXN+5];
struct event{int opt,x,y;}q[MAXN+5];
vector<int>g[MAXN+5];
int f[MAXN+5],dep[MAXN+5],res[MAXN+5],rt[MAXN+5];
unsigned short v[MAXN+5][35];
int find(int x){return (!f[x])?x:find(f[x]);}
tuple<int,int,int>merge(int x,int y){
	x=find(x);y=find(y);if(x==y)return mt(-1,-1,-1);
	if(dep[x]<dep[y])swap(x,y);
	tuple<int,int,int>res=mt(x,y,dep[x]==dep[y]);
	dep[x]+=(dep[y]==dep[x]);f[y]=x;
	for(int i=1;i<=blk_cnt;i++)v[x][i]+=v[y][i];
	return res;
}
void undo(tuple<int,int,int>t){
	int x=get<0>(t),y=get<1>(t),z=get<2>(t);
	if(x==-1)return;f[y]=0;dep[x]-=z;
	for(int i=1;i<=blk_cnt;i++)v[x][i]-=v[y][i];
}
void dfs(int x){
	tuple<int,int,int>tmp;
	if(q[x].opt==1)tmp=merge(q[x].x,q[x].y);
	else if(q[x].opt==3&&!res[x]){
		int rt=find(q[x].x);
		for(int i=1;i<=blk_cnt;i++){
			if(q[x].y<=v[rt][i]){
				for(int j=L[i];j<=R[i];j++){
					if(find(ord[j])==rt)q[x].y--;
					if(!q[x].y){res[x]=j;break;}
				}
				break;
			}else q[x].y-=v[rt][i];
		}
	}
	for(int y:g[x])dfs(y);
	if(q[x].opt==1)undo(tmp);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),ord[i]=i;
	sort(ord+1,ord+n+1,[&](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].opt,&q[i].x);
		if(q[i].opt!=2)scanf("%d",&q[i].y);
	}
	for(int i=1;i<=m;i++){
		if(q[i].opt==2)g[q[i].x].pb(i);
		else g[i-1].pb(i);
	}
	a[0]=-1;blk_sz=3000;blk_cnt=(n-1)/blk_sz+1;
	for(int i=1;i<=blk_cnt;i++){
		L[i]=(i-1)*blk_sz+1;R[i]=min(i*blk_sz,n);
		for(int j=L[i];j<=R[i];j++)bel[j]=i;
	}
	for(int i=1;i<=blk_cnt;i++)for(int j=L[i];j<=R[i];j++)v[ord[j]][i]=1;
	dfs(0);
	for(int i=1;i<=m;i++)if(q[i].opt==3)printf("%d\n",a[ord[res[i]]]);
	return 0;
}