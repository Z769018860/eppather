#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5,inf = 1e9;
typedef long long ll;
int n,Q,Len;
int val[N],ton[N],ts[N];
struct node {
	int c;ll s;
	node(){}
	node(const int _c,const ll _s):c(_c),s(_s){}
	node operator + (const node &rhs) const { return node(c + rhs.c,s + rhs.s);}
};
namespace SEGA {
	const int Sz = N << 2;
	
	int tag[Sz],Mn[Sz];node tr[Sz]; 
	void Add(int k,int v) { tag[k] += v;Mn[k] += v;}
	void pushdown(int k) {
		if(tag[k]) Add(k << 1,tag[k]),Add(k << 1 | 1,tag[k]),tag[k] = 0;
	}
	node Calc(int k,int l,int r,int pre) {
		if(l == r) { int v = max(0,pre - Mn[k]);return node(v,l * v); }
		int mid = l + r >> 1;
		pushdown(k);
		if(pre < Mn[k << 1])
			return Calc(k << 1 | 1,mid + 1,r,pre);
		else return Calc(k << 1,l,mid,pre) + tr[k << 1 | 1];
	}
	void pushup(int k,int md,int r) {
		Mn[k] = min(Mn[k << 1],Mn[k << 1 | 1]);
		tr[k << 1 | 1] = Calc(k << 1 | 1,md + 1,r,Mn[k << 1]);
	}
	void Change(int k,int l,int r,int pos) {
		if(l == r) return;
		int mid = l + r >> 1;
		pushdown(k);
		if(pos <= mid) Change(k << 1,l,mid,pos);
		else Change(k << 1 | 1,mid + 1,r,pos);
		pushup(k,mid,r);
	}
	void modify(int k,int l,int r,int x,int y,int v) {
		if(x <= l && r <= y) return Add(k,v);
		int mid = l + r >> 1;
		pushdown(k);
		if(x <= mid) modify(k << 1,l,mid,x,y,v);
		if(mid < y) modify(k << 1 | 1,mid + 1,r,x,y,v);
		pushup(k,mid,r);
	}
	node Query(int k,int l,int r,int x,int y,int &pre) {
		if(x <= l && r <= y) { node res = Calc(k,l,r,pre);pre = min(pre,Mn[k]);return res;}
		int mid = l + r >> 1;
		pushdown(k);
		if(y <= mid) return Query(k << 1,l,mid,x,y,pre);
		else if(x > mid) return Query(k << 1 | 1,mid + 1,r,x,y,pre);
		else { 
			node res = Query(k << 1,l,mid,x,y,pre);
			res = res + Query(k << 1 | 1,mid + 1,r,x,y,pre);
			return res;
		}
	}
	int QueryMn(int k,int l,int r,int x,int y) {
		if(x <= l && r <= y) return Mn[k];
		int mid = l + r >> 1;
		pushdown(k);
		if(y <= mid) return QueryMn(k << 1,l,mid,x,y);
		else if(x > mid) return QueryMn(k << 1 | 1,mid + 1,r,x,y);
		else return min(QueryMn(k << 1,l,mid,x,y),QueryMn(k << 1 | 1,mid + 1,r,x,y));
	}
	void build(int k,int l,int r) {
		tag[k] = 0;
		if(l == r) { Mn[k] = l - ts[l];return;}
		int mid = l + r >> 1;
		build(k << 1,l,mid);build(k << 1 | 1,mid + 1,r);
		pushup(k,mid,r);
	}
}

namespace SEGB {
	const int Sz = N << 2;
	
	int Mn[Sz],tag[Sz];
	node tr[Sz];
	
	void Add(int k,int v) { tag[k] += v;Mn[k] += v;}
	void pushdown(int k) {
		if(tag[k]) Add(k << 1,tag[k]),Add(k << 1 | 1,tag[k]),tag[k] = 0;
	}	
	node Calc(int k,int l,int r,int suf) {
		if(l == r) { int v = (!ton[l]) && (Mn[k] <= suf);return node(v,l * v);}
		int mid = l + r >> 1;pushdown(k);
		if(suf < Mn[k << 1 | 1])
			return Calc(k << 1,l,mid,suf);
		else return tr[k << 1] + Calc(k << 1 | 1,mid + 1,r,suf);
	}
	void pushup(int k,int l,int md) {
		Mn[k] = min(Mn[k << 1],Mn[k << 1 | 1]);
		tr[k << 1] = Calc(k << 1,l,md,Mn[k << 1 | 1]);
	}
	void Change(int k,int l,int r,int pos) {
		if(l == r) return;
		int mid = l + r >> 1;
		pushdown(k);
		if(pos <= mid) Change(k << 1,l,mid,pos);
		else Change(k << 1 | 1,mid + 1,r,pos);
		pushup(k,l,mid);
	}
	void modify(int k,int l,int r,int x,int y,int v) {
		if(x <= l && r <= y) return Add(k,v);
		int mid = l + r >> 1;
		pushdown(k);
		if(x <= mid) modify(k << 1,l,mid,x,y,v);
		if(mid < y) modify(k << 1 | 1,mid + 1,r,x,y,v);
		pushup(k,l,mid);  
	}
	node Query(int k,int l,int r,int x,int y,int &suf) {
		if(x <= l && r <= y) { node res = Calc(k,l,r,suf);suf = min(suf,Mn[k]);return res;}
		int mid = l + r >> 1;
		pushdown(k);
		if(y <= mid) return Query(k << 1,l,mid,x,y,suf);
		else if(x > mid) return Query(k << 1 | 1,mid + 1,r,x,y,suf);
		else {
			node res = Query(k << 1 | 1,mid + 1,r,x,y,suf);
			res = res + Query(k << 1,l,mid,x,y,suf);
			return res;
		}
	}
	vector<tuple<int,int,int> > Qus;
	void Getpos(int k,int l,int r,int x,int y) {
		if(x <= l && r <= y) { Qus.emplace_back(k,l,r);return;}
		int mid = l + r >> 1;
		if(x <= mid) Getpos(k << 1,l,mid,x,y);
		if(mid < y) Getpos(k << 1 | 1,mid + 1,r,x,y);
	}
	int whole_erfen(int k,int l,int r,int bound,int suf) {
		if(l == r) return l;
		int mid = l + r >> 1;pushdown(k);
		int val = Calc(k << 1 | 1,mid + 1,r,suf).c;
		if(val >= bound)
			return whole_erfen(k << 1 | 1,mid + 1,r,bound,suf);
		else return whole_erfen(k << 1,l,mid,bound - val,min(suf,Mn[k << 1 | 1]));
	}
	int erfen(int x,int y,int bound,int suf) {
		Qus.clear();assert(x <= y);
		int tmp = suf,cnt = Query(1,1,Len,x,y,tmp).c;
		
		assert(cnt >= bound);
		Getpos(1,1,n + n,x,y);
		for(int i = (int)Qus.size() - 1;i >= 0;i--) {
			int k = get<0>(Qus[i]),l = get<1>(Qus[i]),r = get<2>(Qus[i]);
			int val = Calc(k,l,r,suf).c;
			if(val >= bound) return whole_erfen(k,l,r,bound,suf);
			bound -= val;suf = min(suf,Mn[k]);
		}
		assert(0);
	}
	void build(int k,int l,int r) {
		tag[k] = 0;
		if(l == r) { Mn[k] = l - ts[l];return;}
		int mid = l + r >> 1;
		build(k << 1,l,mid);build(k << 1 | 1,mid + 1,r);
		pushup(k,l,mid);
	}
}
inline ll Solve(int L,int R) {
	
	if(L == R) {
		int prv = SEGA::QueryMn(1,1,Len,L,L);
		node tmp(ton[L],1ll * L * ton[L]);
		if(R < Len) tmp = tmp + SEGA::Query(1,1,Len,R + 1,Len,prv);
		int tim = tmp.c;ll ans = tmp.s;
		

		if(!tim) return ans;
		ans += L;
		if(tim == 1) return ans;
		int pos = SEGB::erfen(1,L - 1,tim - 1,inf); 
		
		prv = inf;
		ans += SEGB::Query(1,1,Len,pos,L - 1,prv).s;
		return ans;
	}
	int prv = L < R ? SEGA::QueryMn(1,1,n + n,L,R - 1) : inf;
	node tmp = SEGA::Query(1,1,n + n,R,n + n,prv);
	ll ans = tmp.s;int tim = tmp.c;prv = inf;
	
	if(!tim) return ans;
	int in_minn = SEGA::QueryMn(1,1,Len,L,R - 1);
	int pos = SEGB::erfen(1,L,tim,in_minn);
	ans += SEGB::Query(1,1,n + n,pos,L,in_minn).s;
	return ans;
}
int main() {
	
	
	cin >> n >> Q;Len = n + n;
	for(int i = 1;i <= n;i++) cin >> val[i],++ton[val[i]];
	for(int i = 1;i <= Len;i++) ts[i] = ts[i - 1] + ton[i];
	SEGA::build(1,1,n + n);
	SEGB::build(1,1,n + n);
	for(int _ = 1;_ <= Q;_++) {
		int op,a,b;
		cin >> op;
		if(op == 1) {
			cin >> a >> b;
			ton[val[a]]--;
			SEGA::modify(1,1,Len,val[a],n + n,1);
			SEGB::modify(1,1,Len,val[a],n + n,1);
			SEGA::Change(1,1,Len,val[a]);SEGB::Change(1,1,Len,val[a]);
			ton[val[a] = b]++;
			SEGA::modify(1,1,Len,b,Len,-1);
			SEGB::modify(1,1,Len,b,Len,-1);
			SEGA::Change(1,1,Len,b);SEGB::Change(1,1,Len,b);
		} else cin >> a >> b,cout << Solve(a,b) << endl;
	}
	return 0;
}

