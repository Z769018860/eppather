
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <ctime>
#include <vector>
#include <functional>
#include <map>

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

char s[1000005]={};
int len,a,b;

void wk() {
    int k=0;
    scanf("%s",s+1);
    len=strlen(s+1);
    if(s[1]=='V') b=0;
    else b=1;
    a=1;
    k=(s[1]=='N');
    for(int i=1;i<=len-1;++i) {
        if(s[i]=='N' && s[i+1]=='N') a=b=0;
        k+=(s[i+1]=='N');
    }
    write(min(a,k)),putchar(32),writeln(min(b,k));
}

signed main() {

    int t;
    read(t);
    while(t--) wk();

    return 0;
}