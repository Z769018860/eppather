#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 1000010, K = 2187, P = 1000003;

int n, m;
int init[K][K];
LL R[N], s[N << 1];
vector<int> mat[P];

int read(){
    int x=0,flag=0;
    char c=getchar();
    while ((c<'0')||(c>'9')){
        if (c=='-')flag=1;
        c=getchar();
    }
    while ((c>='0')&&(c<='9')){
        x=x*10+c-'0';
        c=getchar();
    }
    if (flag)x=-x;
    return x;
}
void write(int x){
    if (x<0){
        putchar('-');
        x=-x;
    }
    int num[11];
    num[0]=0;
    while (x){
        num[++num[0]]=x%10;
        x/=10;
    }
    if (!num[0])putchar('0');
    for(int i=num[0];i;i--)putchar(num[i]+'0');
    putchar('\n');
}

int add_low(int a, int b)
{
    int s = 1, res = 0;
    for (int i = 0; i < 7; i ++ )
    {
        res = res + (a + b) % 3 * s;
        s *= 3, a /= 3, b /= 3;
    }
    return res;
}

LL add_high(LL a, LL b)
{
    LL s = 1, res = 0;
    for (int i = 0; i < 5; i ++ )
    {
        res = res + init[a % K][b % K] * s;
        s *= K, a /= K, b /= K;
    }
    return res;
}

int main()
{
    srand(time(0));
    for (int i = 0; i < K; i ++ )
        for (int j = 0; j < K; j ++ )
            init[i][j] = add_low(i, j);
    n = read(), m = read();
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 0; j < 35; j ++ ) R[i] = R[i] * 3 + rand() % 3;
        mat[R[i] % P].push_back(i);
        mat[add_high(R[i], R[i]) % P].push_back(i);
    }
    
    for (int i = 1, a, b, ans = 0; i <= m; i ++ )
    {
        a = read(), b = read();
        a ^= ans, b ^= ans;
        s[i] = add_high(s[b], R[a]);
        if (!s[i]) ans = -1;
        else
        {
            ans = -2;
            for (int j = 0; j < mat[s[i] % P].size(); j ++ )
            {
                LL x = R[mat[s[i] % P][j]];
                if (x == s[i] || add_high(x, x) == s[i])
                {
                    ans = mat[s[i] % P][j];
                    break;
                }
            }
        }
        write(ans);
    }
    
    return 0;
}
