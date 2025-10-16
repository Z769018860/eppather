#include<bits/stdc++.h>
using namespace std;
namespace ac{
	const int MAXN = 6000005;
	int x, a[MAXN], n, last;
	struct interesting{
		int a[30], sz;
		void insert(int v){
			sz++;
			for(int i = 29;~i;i--) a[i] += v >> i & 1;
		}
		long long sum(){
			long long ans = 0;
			for(int i = 29;~i;i--) ans += (1ll << i) * (x >> i & 1 ? sz - a[i] : a[i]);
			return ans;
		}
		long long d(int d){
			long long ans = 0;
			for(int i = 29;~i;i--) ans += 1ll * ((bool(a[i]) ^ (x >> i & 1)) << i) * d;
			return ans;
		}
	}s[MAXN];
	void add(int v){
		a[++n] = v ^ x;
		s[n] = s[n - 1];
		s[n].insert(v ^ x);
	}
	struct node{
		int son[2];
		interesting v;
	}trie[MAXN];
	int cnt = 1;
	void insert(int a){
		int u = 1;
		for(int i = 29;~i;i--){
			int tmp = a >> i & 1;
			if(!trie[u].son[tmp]) trie[u].son[tmp] = ++cnt;
			u = trie[u].son[tmp];
			trie[u].v.insert(a);
		}
	}
	int fk;
	long long query(int r){
		if(r > last) return s[r].sum();
		int u = 1, ls, rs;
		long long ans = 0;
		for(int i = 29;~i;i--){
			ls = trie[u].son[0], rs = trie[u].son[1];
			if(fk >> i & 1) swap(ls, rs);
			if(r <= trie[ls].v.sz) u = ls;
			else{
				ans += trie[ls].v.sum();
				r -= trie[ls].v.sz;
				u = rs;
			}
		}
		return ans + trie[u].v.d(r);
	}
	int main(){
		int N, m, op, aa, l, r;
		scanf("%d", &N);
		for(int i = 1;i <= N;i++){
			scanf("%d", &aa);
			add(aa);
		}
		scanf("%d", &m);
		while(m--){
			scanf("%d", &op);
			if(op == 1){
				scanf("%d", &aa);
				add(aa);
			}
			else if(op == 2){
				scanf("%d%d", &l, &r);
				printf("%lld\n", query(r) - query(l - 1));
			} 
			else if(op == 3){
				scanf("%d", &aa);
				x ^= aa;
			}
			else for(fk = x;last < n;) insert(a[++last]);
		}
		return 0;
	}
} 
signed main(){
	return ac::main();
}