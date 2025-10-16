#include <bits/stdc++.h>
using namespace std;
const int N = (1<<25)+1,M=1e7;
int n,opt,x;
struct BIT{
    int t[N];
    void add(int x,int c){x+=M;for(;x<N;x+=x&-x)t[x]+=c;}
    int query(int x){x+=M;int res=0;for(;x;x^=x&-x)res+=t[x];return res;}
    int kth(int k){
        int x = 0;
        for(int i = 25;~i;--i)if(t[x|(1<<i)]<k)x|=(1<<i),k-=t[x];
        return x+1-M;
    }
}b;
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin >> n;
    while(n--){
        cin >> opt >> x;
        if(opt==1)b.add(x,1);
        else if(opt==2)b.add(x,-1);
        else if(opt == 3)cout << b.query(x-1)+1 << "\n";
        else if(opt == 4)cout << b.kth(x) << "\n";
        else if(opt == 5)cout << b.kth(b.query(x-1)) << "\n";
        else cout << b.kth(b.query(x)+1) << "\n";
    }
    return 0;
}