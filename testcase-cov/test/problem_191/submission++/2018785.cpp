#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second
#define all(v) v.begin(),v.end()
#define sz(v) ((i64)v.size())
#define pq priority_queue

using i64 = long long;
using u64 = unsigned long long;
using pii = pair<int,int>;
using pll = pair<i64,i64>;
using i128 = __int128;

void solve(){
    int n,m;
    cin >> n >> m;
    vector<pii> E(m);
    vector<int> d(n+1);
    for(auto &[u,v]:E){
        cin >> u >> v;
        d[u] ++;
        d[v] ++;
    }
    vector<vector<int>> e(n+1);
    for(auto [u,v]:E){
        if(d[u] > d[v] || (d[u] == d[v] && u > v))swap(u,v);
        
        e[u].push_back(v);
    }
    vector<int> vistime(n+1);
    map<pii,int> cnt1;  
    map<pii,int> cnt2;  
    
    
    
    i64 ans = 0;
    for(int A = 1; A <= n; A ++ ){
        for(auto B:e[A]){
            for(auto C:e[B]){
                cnt1[{A,C}] ++;
            }
        }
    }
    for(int B = 1; B <= n; B ++ ){
        for(int i = 0; i < sz(e[B]); i ++ ){
            auto A = e[B][i];
            for(int j = i+1; j < sz(e[B]); j ++ ){
                auto C = e[B][j];
                cnt2[{min(A,C),max(A,C)}] ++;
            }   
        }
    }
    for(auto [pr,c]:cnt1){
        ans += (i64)c*(c-1)/2;
        
    }
    for(auto [pr,c]:cnt2){
        ans += (i64)c*(c-1)/2;
        
    }
    for(auto [pr,c]:cnt1){
        auto [A,C] = pr;
        ans += c*cnt2[{min(A,C),max(A,C)}];
    }
    cout << ans;
}   
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int T = 1;
    
    for(int i = 1; i <= T; i ++ ){
        solve();
        if(i != T)cout << '\n';
    }
    return 0;
}