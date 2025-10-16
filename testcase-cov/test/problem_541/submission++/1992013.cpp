
#include <bits/stdc++.h>
#define rep(i, f, t) for(int i(f); i <= t; ++i)
#define re(i, t) for(int i(1); i <= t; ++i)
#define per(i, t, f) for(int i(t); i >= f; --i)
#define pe(i, t) for(int i(t); i >= 1; --i) 
#define nx(i, u) for(int i(head[u]); i; i = e[i].nxt)
typedef long long ll;
typedef unsigned long long ull; 
using namespace std;
typedef pair <int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r))  
#define mp(i, j) (make_pair(i, j))

#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f   

const int N = 2e6 + 5;
#include<cstdio>

namespace IO{
	int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}

	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}

	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;

int vis[N];
unsigned int cur_ans;
int p[N], in[N], val[N];
int q[N], l, r, mx, now;
int id[N], tot;

void solve (int pos, int d) {
	int u = p[pos];
	if(d == 1) {
		if(u == -1) {
			return ;
		}
		if(!vis[u]) {
			if(!in[u]) {
				in[u] = 1;
				vis[u] = 1;
				while(vis[mx+1]) {
					++mx;
				}
				cur_ans = mx + 1;
			}
		}
		return ; 
	}
	if(u == -1) {
		if(l <= r) {
			++now; 
			in[val[now]] = 1;
			if(id[q[l]] == now) ++l;
		} 
		else return ;
	}
	else {
		if(vis[u]) {
			if(in[u]) {
				while(l <= r && p[q[r]] >= u) {
					--r;
				}
				q[++r] = pos;
				++tot;
				id[pos] = tot;
				val[tot] = u;
				in[u] = 0;
			}
			else {
				if(l <= r) {
					++now; 
					in[val[now]] = 1;
					if(id[q[l]] == now) ++l;
				} 
				else return ;
			}
		}
		else {
			vis[u] = 1;
			in[u] = 1;
			while(vis[mx+1]) {
				++mx;
			}
		}
	}  
	if(l > r) cur_ans = mx + 1;
	else cur_ans = min(mx + 1, p[q[l]]);
}

int main(){ 
	int T;read(T);
	int m,a,b,d; 
	while(T--){
		unsigned int ans_sum=0;  
		init_case(m,a,b,d,p);
		rep(i, 0, b + 1) vis[i] = in[i] = 0;
		rep(i, 0, a) vis[i] = in[i] = 1;
		mx = a; tot = 0; 
		l = 1, r = 0, now = 0;
		for(int i=1;i<=m;i++){
			cur_ans=0;
			solve(i, d);  
			update_ans(ans_sum,cur_ans,i);
		}
		printf("%u\n",ans_sum);
	}
	return 0;
}  