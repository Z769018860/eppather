#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

int n,a[Maxn+5],t[Maxn+5];
#define lowbit(x) (x&-x)
inline void Add(int x) {while(x<=n) t[x]++,x+=lowbit(x);}
inline int Count(int x) {int res=0; while(x) res+=t[x],x-=lowbit(x); return res;}
inline int Get(string s)
{
    int res=0,w=1;
    for(auto i:s)
    {
        if(i=='-') {w=-1; continue;}
        res=res*10+i-'0';
    }
    return res*w;
}

int main()
{
    

    cin>>n; int chk=0;
    if(n==1) {puts("L"); return 0;}
    For(i,1,n)
    {
        string s; cin>>s;
        if(s[0]=='X') {chk++; continue;}
        a[i]=Get(s);
    }
    if(chk) {puts(chk&1?"W":"L"); return 0;}
    vector<int> v;
    For(i,1,n) v.push_back(a[i]);
    sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());
    For(i,1,n) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
    int ans=0;
    For(i,1,n) ans^=(Count(n)-Count(a[i])),Add(a[i]);
    if(ans&1) puts("W"); else puts("L");
    return 0;
}