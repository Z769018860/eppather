#include <bits/stdc++.h>
#include <ext/rope>
using namespace __gnu_cxx;
#define ll long long
using namespace std;
rope<int> v[300010];
int cnt;
void solve(){
    int n;
    cin >> n;
    rope<int> rp;
    v[cnt++] = rp;
    while(n--){
        int opt;
        cin >> opt;
        if(opt == 1){
            int t,k,x;
            cin >> t >> k >> x;
            rope<int> tmp = v[t];
            tmp.insert(k - 1,x);
            v[cnt++] = tmp;
        }
        else if(opt == 2){
            int t,k;
            cin >> t >> k;
            rope<int> tmp = v[t];
            tmp.erase(k-1,1);
            v[cnt++] = tmp;
        }
        else{
            int t,k;
            cin >> t >> k;
            cout << v[t][k-1]<<endl;
        }
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    
    while(t--) solve();
    return 0;
}