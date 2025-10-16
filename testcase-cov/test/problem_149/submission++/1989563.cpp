#include<bits/stdc++.h>
using namespace std;
int n, k;
double e = 5e-5;
const int N = 1e5 + 5;
int a[N] = {}, b[N] = {};
double d[N] = {};
bool check(double x) {
    for (int i = 1; i <= n; i++)
    {
        d[i] = a[i] * 1.0 - x * b[i];
    }
    sort(d + 1, d + n + 1);
    
    double sum = 0;
    for (int i = 1; i <= k; i++)
    {
        sum += d[n - i + 1];
    }
     return sum >= 0;
}

int main (){
    cin >> n>> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    double l = 0, r = 1.0;
    while (r - l >= e)
    {
        double mid = (r + l) / 2.0;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << r;

    return 0;
}