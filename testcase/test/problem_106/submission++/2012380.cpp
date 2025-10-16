#include<bits/stdc++.h>
#define tp template <typename T>
#define maxn 50001
#define upd(k) treap[k].size = treap[treap[k].l].size+treap[treap[k].r].size+1
#define argu int ll,int rr,ci val
typedef const int & ci;
namespace io{
	#define MAXSIZE 10000000
	struct istream{
		#define gc p1==p2 && (p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin))==buf ? EOF : *p1++
		char buf[MAXSIZE],*p1,*p2,c;
		istream(){p1 = p2 = buf;}
		tp istream& operator >> (T &n){
			bool f = 0;
			do{
				c = gc;
				if (c == '-')f = 1;
			}while (c < '0' || c > '9');
			n = 0;
			while ('0' <= c && c <= '9'){
				n = (n << 3) + (n << 1) + (c ^ '0');
				c = gc;
			}
			if (f)n = -n;
			return *this;
		}
		~istream(){fclose(stdin);}
		#undef gc
	}cin;
	struct ostream{
		char buf[MAXSIZE],*p,t[21];
		ostream():p(buf){}
		void pc(const char &c){
			if (p - buf == MAXSIZE){
				fwrite(buf,1,MAXSIZE,stdout);
				p = buf;
			}
			*p++ = c;
		}
		ostream& operator << (const char &c){
			pc(c);
			return *this;
		}
		tp ostream& operator << (T n){
			if (n < 10){
				pc(n ^ '0');
				return *this;
			}
			for (t[0] = 0;n;n /= 10)
				t[++t[0]] = n % 10 ^ '0';
			while (t[0])pc(t[t[0]--]);
			return *this;
		}
		~ostream(){
			fwrite(buf,1,p - buf,stdout);
			fclose(stdout);
		}
	}cout;
}
using namespace io;
using std::max;
using std::min;
const int MAX = INT_MAX,MIN = -MAX;
std::mt19937 rnd(time(0));
struct node{
	int l,r,w,rd,size;
	node(const int &w = 0):w(w),rd(rnd()),size(1){l = r = 0;}
}treap[850001];
int cnt,x,y,z,reuse[850001];
class fhq{
	int root;
	public:
	void split(ci rt,ci k,int &x,int &y){
		if (!rt)x = y = 0;
		else if (treap[rt].w >= k){
			split(treap[rt].l,k,x,y);
			treap[rt].l = y;
			upd(rt);
			y = rt;
		}else{
			split(treap[rt].r,k,x,y);
			treap[rt].r = x;
			upd(rt);
			x = rt;
		}
	}
	ci merge(ci k1,ci k2){
		if (!k1)return k2;
		if (!k2)return k1;
		if (treap[k1].rd < treap[k2].rd){
			treap[k1].r = merge(treap[k1].r,k2);
			upd(k1);
			return k1;
		}else{
			treap[k2].l = merge(k1,treap[k2].l);
			upd(k2);
			return k2;
		}
	}
	void insert(ci val){
		split(root,val,x,y);
		if (reuse[0]){
			treap[reuse[reuse[0]]] = node(val);
			root = merge(merge(x,reuse[reuse[0]--]),y);
		}else{
			treap[++cnt] = node(val);
			root = merge(merge(x,cnt),y);
		}
	}
	void erase(ci val){
		split(root,val,x,y);
		root = y;
		split(root,val + 1,y,z);
		reuse[++reuse[0]] = y;
		root = merge(merge(x,merge(treap[y].l,treap[y].r)),z);
	}
	int rk(ci val){
		split(root,val,x,y);
		int res = treap[x].size;
		root = merge(x,y);
		return res;
	}
	ci kth(int k){
		if (k <= 0)return MIN;
		if (k > treap[root].size)
			return MAX;
		int rt = root;
		while (k){
			if (treap[treap[rt].l].size >= k)
				rt = treap[rt].l;
			else if (treap[treap[rt].l].size + 1 == k)
				break;
			else{
				k -= treap[treap[rt].l].size + 1;
				rt = treap[rt].r;
			}
		}
		return treap[rt].w;
	}
	ci pre(ci val){
		return kth(rk(val));
	}
	ci suf(ci val){
		return kth(rk(val + 1) + 1);
	}
};
struct seg_tree{
	fhq treap;
}tr[131072];
int n,N,a[maxn];
#define ls k << 1
#define rs k << 1 | 1
#define l tr[k].l
#define r tr[k].r
#define mid tr[k].mid
inline int rk(argu){
	int res = 0;
	for (ll += N - 1,rr += N + 1;ll ^ rr ^ 1;ll >>= 1,rr >>= 1){
		if (~ll & 1)res += tr[ll ^ 1].treap.rk(val);
		if (rr & 1)res += tr[rr ^ 1].treap.rk(val);
	}
	return res;
}
inline void modify(ci pos,ci val){
	for (int i = pos + N;i;i >>= 1){
		tr[i].treap.erase(a[pos]);
		tr[i].treap.insert(val);
	}
}
inline int pre(argu){
	int res = MIN;
	for (ll += N - 1,rr += N + 1;ll ^ rr ^ 1;ll >>= 1,rr >>= 1){
		if (~ll & 1)res = max(res,tr[ll ^ 1].treap.pre(val));
		if (rr & 1)res = max(res,tr[rr ^ 1].treap.pre(val));
	}
	return res;
}
inline int suf(argu){
	int res = MAX;
	for (ll += N - 1,rr += N + 1;ll ^ rr ^ 1;ll >>= 1,rr >>= 1){
		if (~ll & 1)res = min(res,tr[ll ^ 1].treap.suf(val));
		if (rr & 1)res = min(res,tr[rr ^ 1].treap.suf(val));
	}
	return res;
}
#undef l
#undef r
#undef mid
inline int kth(ci L,ci R,ci k){
	int l = 0,r = 1e8,mid;
	while (l < r){
		mid = l + r + 1 >> 1;
		if (rk(L,R,mid) < k)
			l = mid;
		else r = mid - 1;
	}
	return l;
}
int main(){


	treap[0].size = 0;
	int m,opt,l,r,k,i;
	cin>>n>>m;
	N = 1 << int(ceil(log2(n)));
	for (i = 1;i <= n;++i){
		cin>>a[i];
		for (k = i + N;k;k >>= 1)
			tr[k].treap.insert(a[i]);
	}
	while (m--){
		cin>>opt>>l>>r;
		if (opt != 3)cin>>k;
		if (opt == 1)
			cout<<rk(l,r,k) + 1<<'\n';
		else if (opt == 2)
			cout<<kth(l,r,k)<<'\n';
		else if (opt == 3){
			modify(l,r);
			a[l] = r;
		}else if (opt == 4)
			cout<<pre(l,r,k)<<'\n';
		else cout<<suf(l,r,k)<<'\n';
	}
	return 0;
}
