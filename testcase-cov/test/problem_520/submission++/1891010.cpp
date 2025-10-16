#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN=1e5+10;

int v[MAXN], n, ans;     

signed main() {
    cin>>n;
    for (int i=1; i<=n; ++i) cin>>v[i], ans+=2*v[i]*v[i];
    sort(v+1,v+1+n,greater<int>());
    int res=0;
    deque<int> q;
    for (int i=1; i<=n; ++i) {
        if (i==1) {
            q.push_back(v[i]); continue;
        }
        if (q.front()>=q.back()) q.push_front(v[i]);
        else q.push_back(v[i]);
    }
    res+=q.front()*q.back();
    int l=0;
    while (q.size()) {
        res+=l*q.front();
        l=q.front();
        q.pop_front();
    }
    ans-=res*2;
    cout<<ans;
    return 0;
}