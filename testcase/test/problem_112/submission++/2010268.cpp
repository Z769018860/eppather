#include<map>
#include<queue>
#include<cmath>
#include<vector>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
	x=0;int f=1;char c=getchar();
	while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
	x*=f;
}

typedef long long LL;
const int N=2e5+10;
int n, m, tot, c[N], ans[N];
struct node{int x, y, z, ans, w;}a[N], b[N], tmp[N];
bool cmp(node n1, node n2) {return n1.x==n2.x?(n1.y==n2.y?n1.z<n2.z:n1.y<n2.y):n1.x<n2.x;}

int lowbit(int x) {return x&-x;}
void add(int x, int k) {for (;x<=m;x+=lowbit(x)) c[x]+=k;}
int getsum(int x) {int res=0;for (;x>=1;x-=lowbit(x)) res+=c[x];return res;}

void cdq(int l, int r)
{
	if (l>=r) return ;
	int mid=(l+r)>>1;
	cdq(l, mid), cdq(mid+1, r);
	int i=l, j=mid+1, k=l;
	while (i<=mid&&j<=r)
	{
		while (i<=mid&&a[i].y<=a[j].y) add(a[i].z, a[i].w), tmp[k++]=a[i++];
		a[j].ans+=getsum(a[j].z), tmp[k++]=a[j++];
	}
	while (i<=mid) add(a[i].z, a[i].w), tmp[k++]=a[i++];
	while (j<=r) a[j].ans+=getsum(a[j].z), tmp[k++]=a[j++];
	for (i=l;i<=mid;i++) add(a[i].z, -a[i].w);
	for (i=l;i<=r;i++) a[i]=tmp[i];
}

int main()
{
	read(n), read(m);
	for (int i=1;i<=n;i++) read(b[i].x), read(b[i].y), read(b[i].z);
	sort(b+1, b+n+1, cmp);
	for (int i=1, cnt=0;i<=n;i++)
	{
		cnt++;
		if (b[i].x!=b[i+1].x||b[i].y!=b[i+1].y||b[i].z!=b[i+1].z) 
			a[++tot]={b[i].x, b[i].y, b[i].z, 0, cnt}, cnt=0;
	}
	cdq(1, tot);
	for (int i=1;i<=tot;i++) ans[a[i].ans+a[i].w-1]+=a[i].w;
	for (int i=0;i<n;i++) printf("%d\n", ans[i]);
	return 0;
}