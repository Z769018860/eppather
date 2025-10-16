
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;

struct nod{
	int l, r;
	mutable int val;
	friend bool operator <(nod x, nod y){
		return x.l < y.l;
	}
};

set<nod> s;
map<int, int> M;
set<nod>::iterator split(int l){
	set<nod>::iterator it = s.lower_bound((nod){l, 0, 0});
	if(it != s.end() && it->l == l)
		return it;
	it--;
	int ls = it->l, rs = it->r, v = it->val;
	s.erase(it);
	s.insert((nod){ls, l - 1, v});
	return s.insert((nod){l, rs, v}).first;
}
void assign(int l, int r, int v){
	set<nod>::iterator itr = split(r + 1), itl = split(l);
	for(set<nod>::iterator it = itl; it != itr; it++)
		M[it->val] -= (it->r) - (it->l) + 1;
	M[v] += (r - l + 1);
	s.erase(itl, itr);
	s.insert((nod){l, r, v});
}
int getans(int l, int r, int k, int v){
	set<nod>::iterator itr = split(r + 1), itl = split(l);
	for(set<nod>::iterator it = itl; it != itr; it++){
		if(it->val != v)
			continue;
		int sum = (it->r) - (it->l) + 1;
		if(k > sum)
			k -= sum;
		else
			return (it->l) + k - 1;
	}
	return 0;
}

int a[100100];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, lst = 1, l, r, k, v;
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		M[a[i]]++;
		if(a[i] != a[lst]){
			s.insert((nod){lst, i - 1, a[lst]});
			lst = i;
		}
	}
	s.insert((nod){lst, n, a[lst]});
	lst = 0;
	while(m--){
		string ch; cin >> ch;
		if(ch[0] == 'Q'){
			cin >> l >> r >> k >> v;
			l ^= lst, r ^= lst, k ^= lst, v ^= lst;
			
			if(k > r - l + 1 || M[v] < k)
				cout << (lst = 0) << "\n";
			else
				cout << (lst = getans(l, r, k, v)) << "\n";
		} else{
			cin >> l >> r >> v;
			l ^= lst, r ^= lst, v ^= lst;
			assign(l, r, v);
		}
	}

	return 0;
}