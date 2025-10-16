#include <bits/stdc++.h>
#define L(i,j,k) for(int i=(j);i<=(k);i=-~i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define lowbit(x) (x&-x)
#define sort std::stable_sort
#define int long long

namespace rsy{
	const int maxn = 1e5 + 10, mod = 998244353;
	typedef std::pair<int,int> pii;
	typedef long long ll;
	typedef unsigned long long ull;
	void chmin(int &x,int c){x=std::min(x,c);}
	void chmax(int &x,int c){x=std::max(x,c);}
	
	int n,m,q,nxor,a[maxn],sum[maxn][30];
	namespace Trie{
		int Xor,cnt,son[maxn*30][2],sum[maxn*30][30],sz[maxn*30];
		void insert(int x){
			int p=0;
			R(i,29,0){
				int s=x>>i&1;
				if(!son[p][s])son[p][s]=++cnt;
				p=son[p][s],sz[p]++;
				L(j,0,29)if(x&(1<<j))sum[p][j]++;
			}
		}
		ll getsum(int x){
			ll res=0;
			L(i,0,29){
				ll now=0;
				if(nxor&(1<<i))now=sz[x]-sum[x][i];
				else now=sum[x][i];
				res+=(now<<i);
			}
			return res;
		}
		ll count(int x){
			if(!x)return 0;
			ll res=0;int p=0;
			R(i,29,0){
				int l=0,r=1;
				if(Xor&(1<<i))std::swap(l,r);
				if(x<=sz[son[p][l]])p=son[p][l];
				else res+=getsum(son[p][l]),x-=sz[son[p][l]],p=son[p][r];
			}
			res+=getsum(p)/sz[p]*x;
			return res;
		}
		int size(){return sz[son[0][0]]+sz[son[0][1]];}
	};
	void insert(int x){
		x^=nxor,a[++m]=x;
		L(i,0,29)sum[m][i]=sum[m-1][i]+((x>>i)&1);
	}
	ll getsum(int x){
		ll res=0;
		L(i,0,29){
			ll now=0;
			if(nxor&(1<<i))now=x-sum[x][i];
			else now=sum[x][i];
			res+=(now<<i);
		}
		return res;
	}
	ll Solve(int x){
		if(x<=Trie::size())return Trie::count(x);
		return Trie::count(Trie::size())+getsum(x-Trie::size());
	}
	void op4(){Trie::Xor=nxor;L(i,1,m)Trie::insert(a[i]);m=0;}
	
	void solve() {
		std::cin>>n;
		L(i,1,n){int x;std::cin>>x,insert(x);}
		std::cin>>q;
		while(q--){
			int op,x,y;
			std::cin>>op;
			if(op==1)std::cin>>x,insert(x);
			if(op==2)std::cin>>x>>y,std::cout<<Solve(y)-Solve(x-1)<<'\n';
			if(op==3)std::cin>>x,nxor^=x;
			if(op==4)op4();
		}
	}
	
	signed main() {

		std::ios::sync_with_stdio(false); 
		std::cin.tie(nullptr);
		int T = 1;
		while (T -- ) solve();
		return 0;
	}
}

signed main() {return rsy::main();}