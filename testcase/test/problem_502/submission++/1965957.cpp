#include<bits/stdc++.h>
#define ull unsigned long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef pair<ull,ull> Pair;
const int Maxn=2e6;
const ull lim=-1;

namespace io {
        const int SIZE = (1 << 21) + 1;
        char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
        
        #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
        
        inline void flush () {
                fwrite (obuf, 1, oS - obuf, stdout);
                oS = obuf;
        }
        
        inline void putc (char x) {
                *oS ++ = x;
                if (oS == oT) flush ();
        }
        
        template <class I>
        inline void gi (I &x) {
                for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
                for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
        }
        
        template <class I>
        inline void print (I x) {
                if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
                while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
                while (qr) putc (qu[qr --]);
        }
        
        struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: putc;
using io :: print;

int n,m,ans; Pair col[Maxn+5],h[Maxn+5];
mt19937_64 rnd(time(0));
map<Pair,int> mp;

inline auto Merge(Pair a,Pair b)
{
    ull a0=lim^a.first^a.second,b0=lim^b.first^b.second;
    ull s1=(a0&b.first)|(a.first&b0)|(a.second&b.second);
    ull s2=(a0&b.second)|(a.second&b0)|(a.first&b.first);
    return make_pair(s1,s2);
}
inline auto Split(Pair a) {swap(a.first,a.second); return a;}

int main()
{
    

    gi(n),gi(m);
    For(i,1,n)
    {
        col[i].first=rnd();
        col[i].second=(lim^col[i].first)&rnd();
        mp[col[i]]=i;
    }
    int s=0; while(m--)
    {
        int a,fa; gi(a),gi(fa),a^=ans,fa^=ans;
        h[++s]=Merge(h[fa],col[a]);
        if(!h[s].first && !h[s].second) ans=-1;
        else
        {
            if(mp.count(h[s])) ans=mp[h[s]];
            else
            {
                auto res=Split(h[s]);
                if(mp.count(res)) ans=mp[res];
                else ans=-2;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}