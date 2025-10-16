
#include <bits/stdc++.h>
using namespace std;
const int N = 10100, mod = 1e9 + 7;
typedef long long ll;
typedef pair<int, int> pll;
int prime[N];
int qmi(ll a,int b,int p){

    ll res=1%p;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
void solve()
{

    int n,p;
    cin >> n>>p;
    
    for(int i=1;i<=n;i++){
        
        printf("%lld\n",qmi(i,p-2,p));
    }
   

   
}
int main()
{
    int t=1;
    
    while (t--)
        solve();
    return 0;
}
