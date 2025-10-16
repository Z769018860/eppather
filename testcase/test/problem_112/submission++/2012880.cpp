#include<bits/stdc++.h>
using namespace std; 
const int N=1e5+10, K=2e5+10;
int n, k, c[K], cnt[K];
struct node{
	int a, b, c, n, s;
	bool operator !=(node y) {return a!=y.a||b!=y.b||c!=y.c;}
	bool operator <(node y) {return a!=y.a?a<y.a:(b!=y.b?b<y.b:c<y.c);}
} a[N], tp[N];
void add(int x, int v) {for(;x<=k;x+=x&-x) c[x]+=v;}
int sum(int x) {int s=0; for(;x;x-=x&-x) s+=c[x]; return s;}
void cdq(int L, int R) {
	if(L==R) return ;
	int mid=(L+R)>>1;
	cdq(L, mid), cdq(mid+1, R);
	for(int i=L,p1=L,p2=mid+1;i<=R;i++) 
		if(p2>R||(p1<=mid&&a[p1].b<=a[p2].b)) add(a[p1].c, a[p1].n), tp[i]=a[p1++];
		else a[p2].s+=sum(a[p2].c), tp[i]=a[p2++];
	for(int i=L;i<=mid;i++) add(a[i].c, -a[i].n);
	for(int i=L;i<=R;i++) a[i]=tp[i];
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++) scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
	sort(a+1, a+1+n);
	int t=0; for(int i=1,c=1;i<=n;i++,c++) if(a[i]!=a[i+1]) a[++t]=a[i], a[t].n=c, c=0;
	cdq(1, t);
	for(int i=1;i<=t;i++) cnt[a[i].s+a[i].n-1]+=a[i].n;
	for(int i=0;i<n;i++) printf("%d\n", cnt[i]);
	return 0;
}