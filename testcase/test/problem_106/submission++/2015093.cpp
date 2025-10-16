#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
namespace furina{
	const int N = 5e4, M = 5e4;
	int n, m, b;
	vector<int> a[N + 10];
	int hash[N + M + 10], cnt_hash;
	int belong[N + 10];
	struct ask{
		int op, l, r, x, t, id;
		bool operator < (ask x){
			if(belong[l] != belong[x.l])
				return belong[l] < belong[x.l];
			if(belong[r] != belong[x.r])
				return belong[r] < belong[x.r];
			return t < x.t;
		}
	} q[M + 10];
	pair<int, int> stk[M + 10];
	int top;
	int ans[M + 10], sum;
	const int SN = 320;
	struct block{
		int l, r, size, lazy;
	} blk[SN + 10];
	int blg[N + M + 10];
	int f[N + M + 10];
	int cnt;
	inline void init(int n){
		int B = sqrt(n) + 0.5;
		for(int i = 1; i <= n; i++){
			if((i - 1) % B == 0)
				blk[cnt].r = i - 1, blk[++cnt].l = i;
			blg[i] = cnt;
		}
		blk[cnt].r = n;
	}
	inline void move(int u, int sign){
		blk[blg[a[u].back()]].size += sign;
		f[a[u].back()] += sign;
	}
	inline void change(int u, int l, int r, int sign){
		if(sign == 1){
			if(l <= stk[u].first && stk[u].first <= r){
				blk[blg[a[stk[u].first].back()]].size--;
				f[a[stk[u].first].back()]--;
				blk[blg[stk[u].second]].size++;
				f[stk[u].second]++;
			}
			a[stk[u].first].push_back(stk[u].second);
		}
		else{
			a[stk[u].first].pop_back();
			if(l <= stk[u].first && stk[u].first <= r){
				blk[blg[stk[u].second]].size--;
				f[stk[u].second]--;
				blk[blg[a[stk[u].first].back()]].size++;
				f[a[stk[u].first].back()]++;
			}
		}
	}
	inline int pre(int u){
		for(int i = u; i >= blk[blg[u]].l; i--)
			if(f[i])
				return i;
		for(int i = blg[u] - 1; i >= 1; i--)
			if(blk[i].size)
				for(int j = blk[i].r; j >= blk[i].l; j--)
					if(f[j])
						return j;
		return 0;
	}
	inline int nxt(int u){
		for(int i = u; i <= blk[blg[u]].r; i++)
			if(f[i])
				return i;
		for(int i = blg[u] + 1; i <= cnt; i++)
			if(blk[i].size)
				for(int j = blk[i].l; j <= blk[i].r; j++)
					if(f[j])
						return j;
		return 0;
	}
	int main(){
		scanf("%d%d", &n, &m);
		for(int i = 1, val; i <= n; i++){
			scanf("%d", &val), a[i].push_back(val);
			hash[++cnt_hash] = val;
		}
		for(int i = 1; i <= m; i++){
			scanf("%d", &q[i].op);
			if(q[i].op == 3){
				top++;
				scanf("%d%d", &stk[top].first, &stk[top].second);
				hash[++cnt_hash] = stk[top].second;
				i--, m--;
			}
			else
				scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].x), q[i].t = top, q[i].id = i;
		}
		sort(hash + 1, hash + cnt_hash + 1);
		cnt_hash = unique(hash + 1, hash + cnt_hash + 1) - hash - 1;
		for(int i = 1; i <= n; i++)
			a[i][0] = lower_bound(hash + 1, hash + cnt_hash + 1, a[i][0]) - hash;
		for(int i = 1; i <= top; i++)
			stk[i].second = lower_bound(hash + 1, hash + cnt_hash + 1, stk[i].second) - hash;
		init(cnt_hash);
		b = n / pow(m, 1.0 / 3) + 1;
		for(int i = 1; i <= n; i++)
			belong[i] = (i - 1) / b + 1;
		sort(q + 1, q + m + 1);
		for(int i = 1, l = 1, r = 0, t = 0; i <= m; i++){
			while(l > q[i].l)
				move(--l, 1);
			while(r < q[i].r)
				move(++r, 1);
			while(l < q[i].l)
				move(l++, -1);
			while(r > q[i].r)
				move(r--, -1);
			while(t < q[i].t)
				change(++t, l, r, 1);
			while(t > q[i].t)
				change(t--, l, r, -1);
			if(q[i].op == 1){
				q[i].x = lower_bound(hash + 1, hash + cnt_hash + 1, q[i].x) - hash;
				int sum = 0;
				for(int j = 1; j < blg[q[i].x]; j++)
					sum += blk[j].size;
				for(int j = blk[blg[q[i].x]].l; j < q[i].x; j++)
					sum += f[j];
				ans[q[i].id] = sum + 1;
			}
			else if(q[i].op == 2){
				int j = 1;
				while(q[i].x - blk[j].size >= 1)
					q[i].x -= blk[j++].size;
				for(int k = blk[j].l; ; k++){
					if(q[i].x - f[k] >= 1)
						q[i].x -= f[k];
					else{
						ans[q[i].id] = hash[k];
						break;
					}
				}
			}
			else if(q[i].op == 4){
				q[i].x = lower_bound(hash + 1, hash + cnt_hash + 1, q[i].x) - hash - 1;
				ans[q[i].id] = hash[pre(q[i].x)];
			}
			else{
				q[i].x = upper_bound(hash + 1, hash + cnt_hash + 1, q[i].x) - hash;
				ans[q[i].id] = hash[nxt(q[i].x)];
			}
		}
		for(int i = 1; i <= m; i++)
			printf("%d\n", ans[i]);
		return 0;
	}
}
int main(){
	return furina::main();
}