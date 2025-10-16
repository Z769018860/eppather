
#include<bits/stdc++.h>
#define up(i,l,r) for(int i=(l);i<=(r);++i)
#define down(i,l,r) for(int i=(l);i>=(r);--i)
#define p_b push_back
#define p1 first
#define p2 second
#define pi pair<int,int>
#define m_p make_pair
#define x1 x114514
#define y1 y114514
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int maxn=1.5e4+10,N=2e6,mod=1e9+7;
const ll inf=9e18;
const double eps=1e-6;
inline int read(){
    int x=0;
    short t=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*t;
}int n,res1[maxn],res2[maxn],LYLAKIOI;
struct node {
	int op,v,w,e;
}d[maxn];
struct SegTree {
	vector<pi>OP[maxn<<2];
	#define ls(p) (p<<1)
	#define rs(p) (p<<1|1)
	void upd(int l,int r,int s,int t,int p,int x,int w){
		if(l<=s&&t<=r){
			OP[p].p_b(m_p(x,w));return;
		}int mid=s+t>>1;
		if(l<=mid)upd(l,r,s,mid,ls(p),x,w);if(r>=mid+1)upd(l,r,mid+1,t,rs(p),x,w);
	}void calc(int s,int t,int p,vector<pi> T){
		for(auto it:OP[p]){
			down(i,1.5e4,it.p1){
				T[i].p1|=T[i-it.p1].p1;
				if(T[i-it.p1].p1)T[i].p2=max(T[i].p2,T[i-it.p1].p2+it.p2);
			}
		}
		if(s==t&&d[s].op==2){
			res1[s]=T[d[s].v].p1,res2[s]=T[d[s].v].p2;
			int dif=res2[s]^res1[s];
			dif*=LYLAKIOI;
			up(j,s+1,n){
				if(d[j].op==1){
					d[j].v-=dif,d[j].w-=dif,d[j].e-=dif;
					upd(j,d[j].e,1,n,1,d[j].v,d[j].w);
				}
				else {
					d[j].v-=dif;break;
				}
			}
		}if(s==t)return;
		int mid=s+t>>1;
		calc(s,mid,ls(p),T),calc(mid+1,t,rs(p),T);
	}
}T;
void slv(){
	n=read(),read(),LYLAKIOI=read();
	up(i,1,n){
		d[i].op=read(),d[i].v=read();
		if(d[i].op==1)d[i].w=read(),d[i].e=read();
	}up(i,1,n){
		if(d[i].op==2)break;

		T.upd(i,d[i].e,1,n,1,d[i].v,d[i].w);
	}vector<pi>v;
	v.resize(1.5e4+5);
	v[0].p1=1;
	T.calc(1,n,1,v);
	up(i,1,n)if(d[i].op==2)printf("%d %d\n",res1[i],res2[i]);
}
int main(){


    slv();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
