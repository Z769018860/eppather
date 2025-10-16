#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	ll my_pow(ll a,ll b,ll mod){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res=(res*a)%mod;
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	ll qpow(ll a,ll b){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	#define db double
	#define pf printf
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define enter pc('\n')
	#define space pc(' ')
	#define fir first
	#define sec second
	#define MP make_pair
	#define il inline
	#define inf 8e18
	#define random(x) rand()*rand()%(x)
	#define inv(a,mod) my_pow((a),(mod-2),(mod))
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
	il void writesp(ll x){
		write(x);
		space;
	}
}
using namespace my_std;
#define goo(u) for(ll i=headd[u];i;i=e[i].nxt)
ll n,m,s,t,head[50050],headd[50050],cnt=1,in[50050],out[50050],ans=0;
ll S,T,dep[50050];
struct node{
	ll nxt,to,w;
}e[1000010];
void add(ll u,ll v,ll ww){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].w=ww;
	head[u]=cnt;
}
il bl bfs(){
	fr(i,0,n+1) headd[i]=head[i];
	fr(i,0,n+1) dep[i]=0;
	dep[S]=1;
	queue<ll> q;
	q.push(S);
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		go(u){
			ll v=e[i].to;
			if(e[i].w>0&&!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[T];
}
ll dfs(ll u,ll sum){
	if(u==T) return sum;
	ll res=0;
	goo(u){
		ll v=e[i].to;
		if(!sum) break;
		if(e[i].w>0&&dep[v]==(dep[u]+1)){
			ll tmp=dfs(v,min(sum,e[i].w));
			e[i].w-=tmp;
			e[i^1].w+=tmp;
			sum-=tmp;
			res+=tmp;
		}
		headd[u]=i;
	}
	return res;
}
int main(){
	n=read();
	m=read();
	s=read();
	t=read();
	fr(i,1,m){
		ll u=read(),v=read(),l=read(),r=read();
		add(u,v,r-l);
		add(v,u,0);
		in[v]+=l;
		out[u]+=l;
	}
	S=0;
	T=n+1;
	fr(i,1,n){
		if(in[i]>out[i]){
			add(S,i,in[i]-out[i]);
			add(i,S,0);
		}
		if(in[i]<out[i]){
			add(i,T,out[i]-in[i]);
			add(T,i,0);
		}
	}
	add(t,s,inf);
	add(s,t,0);
	while(bfs()) dfs(S,inf);
	go(S){
		if(e[i].w){
			pf("please go home to sleep");
			return 0;
		}
	}
	ans=e[cnt].w;
	head[s]=e[head[s]].nxt;
	head[t]=e[head[t]].nxt;
	S=t;
	T=s;
	while(bfs()) ans-=dfs(S,inf);
	write(ans);
}