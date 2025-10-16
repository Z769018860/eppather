#include <bits/stdc++.h>
using namespace std;

#define int long long 

int n,m;

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
	BIT arr(n);
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		arr.modify(i,x);
	}
	while(m--){
		int op,a,b;
		cin>>op>>a>>b;
		if(op==1){
			arr.modify(a,b);
		}else{
			cout<<arr.query(a,b)<<'\n';
		}
	}
}