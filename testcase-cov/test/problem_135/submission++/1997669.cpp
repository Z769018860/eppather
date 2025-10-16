#include<iostream>
using namespace std;
typedef long long ll; 
const int N = 2049;
ll lowbit(ll x)
{
	return (x&-x);
}
ll t1[N][N],t2[N][N],t3[N][N],t4[N][N];
ll n,m;
void add(ll x, ll y, ll val)
{
    ll val1 = val;
    ll val2 = 1ll * val * x;
    ll val3 = 1ll * val * y;
    ll val4 = 1ll * val * x * y;
    while(x <= n)
    {
        ll ty = y;
        while(ty <= m)
        {
            t1[x][ty] += val1;
            t2[x][ty] += val2;
            t3[x][ty] += val3;
            t4[x][ty] += val4;
            ty += lowbit(ty);
        }
        x += lowbit(x);
    }
}
void add(ll x0, ll y0, ll x1, ll y1, ll val)
{
    add(x0, y0, val);
	add(x0, y1 + 1, -val);
	add(x1 + 1, y0, -val);
	add(x1 + 1, y1 + 1, val);
}

ll query(ll x, ll y)
{
    ll sum1 = 0;
    ll sum2 = 0;
    ll sum3 = 0;
    ll sum4 = 0;
    ll xx = x,yy = y;
    while(x >= 1)
    {
        ll ty = y;
        while(ty >= 1)
        {
            sum1 += t1[x][ty];
        	sum2 += t2[x][ty];
            sum3 += t3[x][ty];
        	sum4 += t4[x][ty];
            ty -= lowbit(ty);
        }
        x -= lowbit(x);
    }
    return ((xx+1) * (yy+1)) *sum1  - (yy+1) * sum2 - (xx+1) * sum3 + sum4;
}
ll query(ll x0, ll y0, ll x1, ll y1)
{
    return query(x1,y1) + query(x0-1,y0-1)-query(x1,y0-1)-query(x0-1,y1);
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    ll k,a,b,c,d,type;
    while(cin>>type)
    {
    	if(type==1)
		{
			cin>>a>>b>>c>>d>>k;;
			add(a,b,k);
			add(a,d+1,-k);
			add(c+1,b,-k);
			add(c+1,d+1,k);
		} 
		else
		{
			cin>>a>>b>>c>>d;
			cout<<query(a,b,c,d)<<endl;
		}
	}
}