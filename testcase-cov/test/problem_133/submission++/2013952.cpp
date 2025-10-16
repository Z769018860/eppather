#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 5005;
int n, m, c[N][N];
void add(int x, int y, int k){
	for(int i = x; i <= n; i += lowbit(i))
		for(int j = y; j <= m; j += lowbit(j))
			c[i][j] += k;
}
int query(int x, int y){  
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		for(int j = y; j; j -= lowbit(j))
			res += c[i][j];
	return res;
}
int query(int a, int b, int c, int d){
	return query(c, d) - query(c, b - 1) - query(a - 1, d) + query(a - 1, b - 1);
}
void Solve(){
	cin >> n >> m;
	int opt, a, b, c, d;
	while(cin >> opt){
		if(opt == 1){
			cin >> a >> b >> c;
			add(a, b, c);
		}
		else{
			cin >> a >> b >> c >> d;
			cout << query(a, b, c, d) << '\n';
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; 
	while(T--) Solve();
	return 0;
}