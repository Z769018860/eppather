bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
const int N=1e5+5,M=2e5+5;
int n,K;
struct node {
	int id,x,y,z,cnt;
}a[N],tmp[N];int alen;
il bool cmp(node x,node y) {
	if(x.x==y.x) {
		if(x.y==y.y) return x.z<y.z;
		return x.y<y.y;
	}
	return x.x<y.x;
}
int ans[N],sum[M],tot[N];
il int lowbit(int k) {return k&-k;}
il void add(int x,int k) {
	while(x<=K) {
		sum[x]+=k;
		x+=lowbit(x);
	}  
}
il int query(int x) {
	int res=0;
	while(x) {
		res+=sum[x];
		x-=lowbit(x);
	}
	return res;
}
il void clear(int x) {
	while(x<=K) {
		if(!sum[x]) return ;
		sum[x]=0;
		x+=lowbit(x);
	}
}
void cdq(int l,int r) {
	if(l>=r) return ;
	int mid=(l+r)>>1,cnt=0;
	cdq(l,mid),cdq(mid+1,r);
	int i=l,j=mid+1;
	for(;j<=r;j++) {
		for(;i<=mid&&a[i].y<=a[j].y;i++) add(a[i].z,a[i].cnt),tmp[++cnt]=a[i];
		ans[a[j].id]+=query(a[j].z);
		tmp[++cnt]=a[j];
	}
	for(;i<=mid;i++) tmp[++cnt]=a[i];
	for(int k=l;k<=mid;k++) clear(a[k].z);
	for(int k=l;k<=r;k++) a[k]=tmp[k-l+1];
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n,K);
	for(int i=1;i<=n;i++) {
		read(a[i].x,a[i].y,a[i].z);
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;) {
		int ix=i+1,cnt=1;
		while(ix<=n&&a[ix].x==a[i].x&&a[ix].y==a[i].y&&a[ix].z==a[i].z) ix++,cnt++;
		a[++alen]=a[i];
		a[a[alen].id=alen].cnt=cnt;
		i=ix;
	}
	cdq(1,alen);
	for(int i=1;i<=alen;i++) tot[ans[a[i].id]+a[i].cnt-1]+=a[i].cnt;
	for(int i=0;i<n;i++) printf("%d\n",tot[i]);
	return 0;
}
