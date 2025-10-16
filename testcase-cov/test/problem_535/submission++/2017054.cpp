#include <bits/stdc++.h>
#define LL long long
#define down 0.996

using namespace std;

const int N = 3e5+5;
int h[N],rt[N],ls[N*22],rs[N*22],ct[N*22],cnt,a[N],b[N],c[N],d[N],las,c1,c2,_x,_y,n,mx;

void ins(int p,int l,int r,int &i)
{
	int tmp = i;i = ++cnt;
	ls[i] = ls[tmp],rs[i] = rs[tmp],ct[i] = ct[tmp];
	if (l == r) return void(ct[i]++);
	int mid = (l+r)>>1;
	if (p <= mid) ins(p,l,mid,ls[i]);
	else ins(p,mid+1,r,rs[i]);
	ct[i] = ct[ls[i]]+ct[rs[i]];
}

int query(int l,int r,int L,int R,int i,int j)
{
	if (!i && !j) return 0;
	if (l >= L && r <= R) return ct[i]-ct[j];
	int mid = (l+r)>>1,res = 0;
	if (mid >= L) res += query(l,mid,L,R,ls[i],ls[j]);
	if (mid+1 <= R) res += query(mid+1,r,L,R,rs[i],rs[j]);
	return res;
}

void SA()
{
	double T = 11451;
	while(T > 1e-7)
	{
		T *= down;
		int x = ((int)(_x+(2*rand()-RAND_MAX)*T)%c1+c1)%c1+1,y = ((int)(_y+(2*rand()-RAND_MAX)*T)%c2+c2)%c2+1;
		if (b[y] >= a[x]-1 || d[y] <= c[x]+1) continue;
		int res = query(1,n,b[y]+1,a[x]-1,rt[d[y]-1],rt[c[x]]),del = res-las;
		if (del > 0 || exp(del*1.0/T)*RAND_MAX > rand()) mx = max(mx,las = res),_x = x,_y = y;
	}
}

int main()
{
	
	
	srand(469378);
	ios::sync_with_stdio(0);
	cin >> n;
	LL ans = 0;
	for (int i = 1;i <= n;i++)
		cin >> h[i],ins(h[i],1,n,rt[i] = rt[i-1]),ans += query(1,n,h[i]+1,n,rt[i],0);
	list < int > q;
	for (int i = 1;i <= n;i++)
		if (q.empty() || h[i] > h[q.back()]) q.push_back(i);
	while(q.size())
	{
		int x = q.front();q.pop_front();
		if (q.size() && q.front() == x+1) continue;
		a[++c1] = h[x],c[c1] = x;
	}
	for (int i = n;i >= 1;i--)
		if (q.empty() || h[i] < h[q.back()]) q.push_back(i);
	while(q.size())
	{
		int x = q.front();q.pop_front();
		if (q.size() && q.front() == x-1) continue;
		b[++c2] = h[x],d[c2] = x;
	}
	reverse(b+1,b+c2+1),reverse(d+1,d+c2+1);
	if(1LL*c1*c2 <= 5e6)
	{
		int res = 0;
		for (int i = 1;i <= c1;i++)
		{
			int p = upper_bound(d+1,d+c2+1,c[i])-d;
			for (int j = p;b[j] < a[i]-1 && j <= c2;j++)
				res = max(res,query(1,n,b[j]+1,a[i]-1,rt[d[j]-1],rt[c[i]]));
		}
		cout << ans-res*2;
	}
	else
	{
		_x = c1/2,_y = c2/2;
		if (b[_y] < a[_x]-1 && d[_y] > c[_x]+1)  mx = las = query(1,n,b[_y]+1,a[_x]-1,rt[d[_y]-1],rt[c[_x]]);
		while(clock()*1.0/CLOCKS_PER_SEC < 0.3) SA();
		cout << ans-mx*2;
	}
	return 0;
}