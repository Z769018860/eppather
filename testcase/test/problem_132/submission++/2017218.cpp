#define _CRT_SECURE_NO_WARNINGS
#define CASE break;case
#define inf 1000000000
#include<iostream>
#include<stdio.h>
#include<bitset>
#include<istream>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<string.h>
#include<ctype.h>
#include<vector>
#include<math.h>
#include<set>
#include<list>
#include<stack>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define mydef  std::ios::sync_with_stdio(false);std::cin.tie(0);
#define endl "\n"
#define mod 1000000007
typedef long long ll;
struct node
{
    node()
    {
        sum = 0;
        lazy = 0;
    }
    ll sum;
    ll lazy;
}; 
node seg[4000005];
ll val[1000005];
ll n, q;
void build(ll cur = 1, ll l = 1, ll r = n)
{
    if (l == r)
    {
        seg[cur].sum = val[l];
        return;
    }
    ll mid = (l + r) / 2;
    build(2 * cur, l, mid);
    build(2 * cur + 1, mid + 1, r);
    seg[cur].sum = seg[cur * 2].sum + seg[cur * 2 + 1].sum;
}
void change(ll dl, ll dr, ll val, ll cur = 1, ll cl = 1, ll cr = n)
{
    if (cl >= dl && cr <= dr)
    {
        seg[cur].lazy += val;
        seg[cur].sum += (cr - cl + 1) * val;
        return;
    }
    ll mid = (cl + cr) / 2;
    seg[2 * cur].lazy += seg[cur].lazy;
    seg[2 * cur].sum += seg[cur].lazy * (mid - cl + 1);
    seg[2 * cur + 1].lazy += seg[cur].lazy;
    seg[2 * cur + 1].sum += seg[cur].lazy * (cr - (mid + 1) + 1);
    seg[cur].lazy = 0;
    if (dr <= mid)change(dl, dr, val, 2 * cur, cl, mid);
    else if(dl>mid)change(dl, dr, val, 2 * cur+1, mid+1, cr);
    else
    {
        change(dl, dr, val, 2 * cur, cl, mid);
        change(dl, dr, val, 2 * cur + 1, mid + 1, cr);
    }
    seg[cur].sum = seg[cur * 2].sum + seg[cur * 2 + 1].sum;
}
ll check(ll dl, ll dr, ll cur = 1, ll cl = 1, ll cr = n)
{
    if (cl >= dl && cr <= dr)
        return seg[cur].sum;
    ll mid = (cl + cr) / 2;
    if(seg[cur].lazy)
    {
        seg[2 * cur].lazy += seg[cur].lazy;
        seg[2 * cur].sum += seg[cur].lazy * (mid - cl + 1);
        seg[2 * cur + 1].lazy += seg[cur].lazy;
        seg[2 * cur + 1].sum += seg[cur].lazy * (cr - (mid + 1) + 1);
        seg[cur].lazy = 0;
    }
    if (dr <= mid)return check(dl, dr, cur * 2, cl, mid);
    else if (dl > mid)return check(dl, dr, cur * 2 + 1, mid + 1, cr);
    else return check(dl, dr, cur * 2, cl, mid) + check(dl, dr, cur * 2 + 1, mid + 1, cr);
}
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    cin >> n >> q;
    for (ll i = 1; i <= n; i++)
        cin >> val[i];
    build();
    ll a, b, c, d;
    while (q--)
    {
        cin >> a;
        if (a == 1)
        {
            cin >> b >> c >> d;
            change(b, c, d);
        }
        else
        {
            cin >> b >> c;
            cout << check(b, c) << endl;
        }
    }
    return 0;
}
