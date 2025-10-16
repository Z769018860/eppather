#include <bits/stdc++.h>
using namespace std;
#define For(i,a,n) for(register int i = a;i<=n;i++)
#define Dec(i,a,n) for(register int i = a;i>=n;i--)
#define CIN const int
#define il inline
#define LOG2(x) __lg(x)
#define int unsigned long long

CIN N = 1e6+5,P = 131;
char s[N],t[N]; 
int hs[N],ht,pp[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	
	cin>>(s + 1);
	cin>>(t + 1);
	int lent = strlen(t +1 );
	int lens = strlen(s + 1);
	For(i,1,lent) ht = ht*P + t[i] - 'a';
	For(i,1,lens) hs[i] = hs[i-1] * P + s[i] - 'a';
	pp[0] = 1;
	For(i,1,lent + 4) pp[i] = pp[i-1]*P;
	int ans = 0;
	For(i,1,lens - lent + 1) {
		int j = i + lent - 1;
		if(hs[j] - hs[i-1]*pp[j - i + 1] == ht) ans++;
	}
	cout<<ans;
	
	return 0;
}
