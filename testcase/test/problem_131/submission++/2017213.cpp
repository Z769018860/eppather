#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int N = 1e6+5;

int n,m;
int a[N];

struct BIT{
	int n;
	vector<int>tr;
	BIT(int m){
		n = m;
		tr.resize(m+1);
	}
	void modify(int p,int x){
		while(p<=n){
			tr[p] += x;
			p += p&(-p);
		}
	}
	int query(int p){
		int res = 0;
		while(p>0){
			res += tr[p];
			p -= p&(-p);
		}
		return res;
	}
	int query(int l,int r){
		return query(r) - query(l-1);
	}
};

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	BIT arr(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(m--){
		int op;
		cin>>op;
		if(op==1){
			int l,r,x;
			cin>>l>>r>>x;
			arr.modify(l,x);
			arr.modify(r+1,-x);
		}else{
			int id;
			cin>>id;
			int ans = a[id] + arr.query(id);
			cout<<ans<<'\n';
		}
	}
}