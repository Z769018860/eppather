#include <bits/stdc++.h>

#define mar(x) for(int i = head[x]; i; i = e[i].nxt)
#define car(x) memset(x, 0, sizeof(x))
#define int long long
constexpr int inf = 1e9 +10;
constexpr int MAXN = 5e5;

using namespace std;

inline int read( ){
	int x = 0, w = 1; char ch = getchar( );
	while(!isdigit(ch)){if(ch == '-') w = -1; ch = getchar( );}
	while(isdigit(ch)){x = x * 10 + ch - '0'; ch = getchar( );}
	return w == 1 ? x : -x;
}
vector<int> p;
int f(int x){
	return x * (x - 1) * (x - 2) / 6;
}
int g[505][505];
int tot;
void build(int x){
	for(int i = tot + 1; i <= tot + x; i++)
		for(int j = i + 1; j <= tot + x; j++)
			g[i][j] = g[j][i] = 1;
	tot += x;
}
signed main( ){
	int n = read( );
	for(int i = 500; i >= 3; i--){
		if(n == 0) break;
		while(n != 0 and n >= f(i)) p.push_back(i), n -= f(i); 
	}
	for(int t: p) build(t);
	cout << tot << '\n';
	for(int i = 1; i <= tot; i++){
		for(int j = i + 1; j <= tot; j++)
			printf("%lld ",g[i][j]);
		putchar('\n');
	}
	fclose(stdin);
	fclose(stdout);	
	return 0;
} 
