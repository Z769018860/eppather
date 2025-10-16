
#include <bits/stdc++.h>

using namespace std; typedef long long ull;



unsigned int T, SA, SB, SC, lastans;
unsigned int rng() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
























































ull nim[256][256];
ull f(ull x,ull y,int len=32) {
    if(x==0||y==0) return 0;
    if(x==1||y==1) return x*y;
    if(len<=4&&nim[x][y]) return nim[x][y];
    ull xa=x>>len,xb=x^(xa<<len),ya=y>>len,yb=y^(ya<<len);
    ull a=f(xb,yb,len>>1),b=f(xa^xb,ya^yb,len>>1),c=f(xa,ya,len>>1),d=f(c,1ull<<len-1,len>>1);
    ull re=((b^a)<<len)^a^d;
    if(len<=4) nim[x][y]=re;
    return re;
}

unsigned tab[16 * 256 * 256];

inline unsigned nim_mul(unsigned x, unsigned y)
{
    unsigned res = 0;
    for (unsigned i = 0; i < 4; i++) for (unsigned j = 0; j < 4; j++)
        res ^= tab[(i << 18) | (j << 16) | (x >> (i << 3) & 255u) << 8 | (y >> (j << 3) & 255u)];
    return res;
}

int main()
{
    scanf("%u%u%u%u", &T, &SA, &SB, &SC);
    for (unsigned i = 0; i < 4; i++) for (unsigned j = 0; j < 4; j++)
        for (unsigned x = 0; x < 256; x++) for (unsigned y = 0; y < 256; y++)
            tab[(i << 18) | (j << 16) | (x << 8) | y] = f(x << (i << 3), y << (j << 3));
    for (int i = 0; i < T; i++)
    {
        unsigned int x = rng() + lastans;
        unsigned int y = rng();
        lastans = nim_mul(x, y);
    }
    return 0 * printf("%u\n", lastans);
}