#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n,k,a[N];
signed main() {
    cin>>k;
    n = k+1;
    cout << n << endl;
    int i = n,x = 1,y = n;
    while(i>0) {
        a[i--] = y--;
        a[i--] = x++;
    }
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}