#include <stdio.h>

#define N 4000001
#define MOD 998244353

int id[N], sz[N];

int read() {
	int s=0, w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}

void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}

int main() {
    int i, j, p, q, n, m, op, ans = 0;
    n = read();
    m = read();
    for(i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
    while(m--) {
        op = read();
        p = read();
        q = read();
        for(i = p; i != id[i]; i = id[i]) {
            id[i] = id[id[i]];
        }
        for(j = q; j != id[j]; j = id[j]) {
            id[j] = id[id[j]];
        }
        if(op == 0) {
            if(i == j) {
                continue;
            }
            if(sz[i] < sz[j]) {
                id[i] = j;
                sz[j] += sz[i];
            } else {
                id[j] = i;
                sz[i] += sz[j];
            }
        } else {
            ans <<= 1;
            ans += (i == j);
            ans %= MOD;
        }
    }
    print(ans);
    putchar('\n');
}