#include<bits/stdc++.h>
using namespace std;
#define fo(v,a,b) for(int v = a; v <= b; v++)
#define fr(v,a,b) for(int v = a; v >= b; v--)
#define cl(a,v) memset(a, v, sizeof(a))

typedef long long ll;

const int N = 70;

int n, p, a[N], f[N][N * N], C[N][N];
inline void add(int &x, int y) {  x = (x + y) % p;  }

int dp[N][N][N * N], pw[N][N];
void prework() {
    fo(i, 0, p - 1) {
        C[i][0] = 1;
        fo(j, 1, i) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
    }
    fo(i, 0, n) {
        pw[i][0] = 1;
        fo(j, 1, p) pw[i][j] = pw[i][j - 1] * a[i] % p;
    }

    fo(j, 0, p - 1) dp[0][j][0] = pw[0][j];
    fo(i, 1, n) fo(j, 0, p - 1) fo(k, 0, j * (i - 1)) if(dp[i - 1][j][k]) {
        fo(v, 0, p - 1 - j)
            add(dp[i][j + v][k + i * v], dp[i - 1][j][k] * pw[i][v] * C[j + v][v]);
    }
    fo(j, 0, p - 1) fo(k, 0, (p - 1) * n) f[j][k] = dp[n][j][k];
}

int res[N][N], cnt;
int Solve(ll m, ll k) {
    cl(res, 0), cnt = 0, res[0][0] = 1;
    while(m) {
        int b = m % p, c = k % p; cnt++;
        
        
        fo(x, 0, n) if(res[cnt - 1][x]) fo(i, 0, n) {
            int y = i * p + (c + p - x % p) % p;
            if(y > n * p || !f[b][y]) continue;
            add(res[cnt][(x + y) / p], res[cnt - 1][x] * f[b][y]);
        }
        m /= p, k /= p;
    }
    return res[cnt][k];
}

int main()
{



    cin >> n >> p;
    fo(i, 0, n) scanf("%d", &a[i]);
    prework();
    
    int Q; cin >> Q;
    while(Q--) {
        ll m, k; scanf("%lld%lld", &m, &k);
        printf("%d\n", Solve(m, k));
    }

    return 0;
}
