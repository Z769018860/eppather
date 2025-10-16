
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <ctime>
#include <vector>
#include <functional>
#include <map>
#include <math.h>

#ifndef ONLINE_JUDGE

#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize ("inline")

#endif

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pd;
#define mkp make_pair
#define fir first
#define sec second

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vll;
typedef vector<pi> vpi;
#define _pb push_back
#define _eb emplace_back

bool _t(char c) {
    return ((c<='9' && c>='0') || c=='-');
}

template <typename Tp> 
void read(Tp &_a) {
    _a=0;
    int flg=1;
    char c;
    while(!_t(c=getchar())) ;
    if(c=='-') flg=-1,c=getchar();
    _a=c-'0';
    while((c=getchar())!='-' && _t(c)) _a=_a*10+c-'0';
    _a*=flg;
}

template <typename Tp> 
Tp read() {
    Tp _a;
    read(_a);
    return _a;
}

template <typename Tp> 
void write(Tp _a) {
    char s[45]={};
    int cnt=0;
    if(_a<0) putchar('-'),_a=-_a;
    if(_a==0) {
        putchar('0');
        return ;
    }
    while(_a) s[++cnt]=_a%10+48,_a/=10;
    while(cnt) putchar(s[cnt--]);
}

template <typename Tp>
void writeln(Tp _a) {
    write(_a),putchar(10);
}

const ll Md=998244353;
ll n,m,Ans,mn;
short mu[4000005]={};
int Pr[4000005]={},cnt=0;
bool vis[4000005]={};

void pre() {
    mu[1]=1;
    for(int i=2;i<=4000000;++i) {
        if(!vis[i]) Pr[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt && 1ll*i*Pr[j]<=4000000;++j) {
            vis[i*Pr[j]]=true;
            if(i%Pr[j]==0) {
                mu[i*Pr[j]]=0;
                break;
            }
            else mu[i*Pr[j]]=-mu[i];
        }
    }
}

void wk() {
    read(n),read(m);
    Ans=0;
    pre();
    mn=min(sqrt(n),sqrt(m));
    for(ll i=1;i<=mn;++i) {
        Ans=(Ans+1ll*mu[i]*((m/(i*i))%Md)%Md*((n/(i*i))%Md)%Md)%Md;
    }
    writeln((Ans+Md)%Md);
}

signed main() {

    int t=1;

    while(t--) wk();

    return 0;
}