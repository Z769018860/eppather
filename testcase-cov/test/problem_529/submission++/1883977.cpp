#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define PII pair<int,int>
#define MP make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define SET(a,b) memset(a,b,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(b))
#define rep(i,j,k) for(int i=(j);i<=(k);++i)
#define per(i,j,k) for(int i=(j);i>=(k);--i)
int read() {
    int a=0, f=1; char c=getchar();
    while(!isdigit(c)) {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(isdigit(c)) a=a*10+c-'0', c=getchar();
    return a*f;
}
const int N=1e6+5;
int T, n;
char s[N];
void solve() {
    scanf("%s",s+1);
    n=strlen(s+1);
    vector<int> a;
    rep(i,1,n) {
        if(s[i]=='N') a.pb(1);
        else if(i==1||s[i-1]=='N') a.pb(2);
    }
    int m=a.size();
    int two=0;
    for(int i=1;i<m;++i) if(a[i]==a[i-1]&&a[i]==1) { two=1; break; }
    if(two) puts("0 0");
    else if(a.size()==1&&a[0]==2) puts("0 0");
    else if(a[0]==2) puts("1 0");
    else puts("1 1");
    
}
signed main() {
    T=read();
    while(T--) solve();
    return 0;
}