#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 1000000007
#define int long long
#define MAXN 1000005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}
template <typename T> inline void chkmax (T &a,T b){a = max (a,b);}
template <typename T> inline void chkmin (T &a,T b){a = min (a,b);}

int A,B,C,L1,R1,L2,R2,X[MAXN],lst[MAXN],app1[MAXN],app2[MAXN],pre[MAXN];
inline int mul (int a,int b){return a * b % mod;}
inline int dec (int a,int b){return a >= b ? a - b : a + mod - b;}
inline int add (int a,int b){return a + b >= mod ? a + b - mod : a + b;}
inline int qkpow (int a,int b){
    int res = 1;for (;b;b >>= 1,a = mul (a,a)) if (b & 1) res = mul (res,a);
    return res;
}
inline void Add (int &a,int b){a = add (a,b);}
inline void Sub (int &a,int b){a = dec (a,b);}

int countit (int pos,int st,int len){
	if (pos >= st) return (pos - st) / len + 1;
	else return 0;
}

signed main(){
	read (A,B,C,X[0],L1,R1,L2,R2),memset (lst,-1,sizeof (lst)),lst[X[0]] = 0;
	for (Int i = 1;i <= C;++ i){
		X[i] = (1ll * A * X[i - 1] % C + B) % C + 1;
		if (~lst[X[i]]){
			for (Int j = 0;j < lst[X[i]];++ j){
				if (L1 <= j && j <= R1) app1[X[j]] ++;
				if (L2 <= j && j <= R2) app2[X[j]] ++;
			}
			int len = i - lst[X[i]];
			for (Int j = lst[X[i]];j < i;++ j){
				if (R1 >= j){
					int t1 = countit (R1,j,len) - countit (L1 - 1,j,len);
					Add (app1[X[j]],t1 % mod);
				}
				if (R2 >= j){
					int t2 = countit (R2,j,len) - countit (L2 - 1,j,len);
					Add (app2[X[j]],t2 % mod);
				}
			}
			break;
		}
		lst[X[i]] = i;
	}
	int ans = 0;
	for (Int i = 1;i <= C;++ i) Add (ans,mul (2,mul (app1[i],app2[i]))),pre[i] = add (pre[i - 1],app2[i]);
	for (Int i = 1;i <= C;++ i) if (app1[i]){
		int up = (int)ceil(C * 1.0 / i + i * 1.0 / C);
		for (Int j = 3,lsv = i;j <= up;++ j){
			int L = lsv + 1,R = C,res = C;
			res = (i * j + sqrt (i * i * j * j - 4 * i * i)) * 0.5;
			chkmin (res,C);
			
			
			
			
			
			
			
			
			Add (ans,mul (mul (j,app1[i]),dec (pre[res],pre[lsv]))),lsv = res;
		}
	}
	for (Int i = 1;i <= C;++ i) pre[i] = add (pre[i - 1],app1[i]);	
	for (Int i = 1;i <= C;++ i) if (app2[i]){
		int up = (int)ceil(C * 1.0 / i + i * 1.0 / C);
		for (Int j = 3,lsv = i;j <= up;++ j){
			int L = lsv + 1,R = C,res = C;
			res = (i * j + sqrt (i * i * j * j - 4 * i * i)) * 0.5;
			chkmin (res,C);
			
			
			
			
			
			
			Add (ans,mul (mul (j,app2[i]),dec (pre[res],pre[lsv]))),lsv = res;
		}
	}
	write (ans),putchar ('\n');
	return 0;
}