#include <bits/stdc++.h>
using namespace std;
#define N 500005
int n,tmp1[N],tmp2[N],o1[N],o2[N],rv1[N],rv2[N];vector<int> a,b,ans;
int f1(int x,int y) {return (rv1[y] && rv1[y]>=x)+(rv2[y] && rv2[y]<x);}
int f2(int x,int y) {return (o1[x] && o1[x]>=y)+(o2[x] && o2[x]<y);}
vector<int> unitMongeMul(vector<int> a,vector<int> b)
{
	if(a.size()==2) return vector<int>({0,1});
	int n=a.size()-1,mid=n/2,tpA1=0,tpA2=0,tpB1=0,tpB2=0;
	vector<int> a1(mid+1),a2(n-mid+1),b1(mid+1),b2(n-mid+1),res1,res2,res(n+1);
	for(int i=1;i<=n;++i)
	{
		if(a[i]<=mid) a1[++tpA1]=a[i];else a2[++tpA2]=a[i]-mid;
		if(b[i]<=mid) b1[++tpB1]=b[i];else b2[++tpB2]=b[i]-mid;
	}res1=unitMongeMul(a1,b1);res2=unitMongeMul(a2,b2);
	tpA1=tpA2=tpB1=tpB2=0;fill(o1+1,o1+n+1,0);fill(o2+1,o2+n+1,0);
	fill(rv1+1,rv1+n+1,0);fill(rv2+1,rv2+n+1,0);
	for(int i=1;i<=n;++i) if(b[i]<=mid) tmp1[++tpB1]=i;else tmp2[++tpB2]=i;
	for(int i=1;i<=n;++i) if(a[i]<=mid) o1[i]=tmp1[res1[++tpA1]];
		else o2[i]=tmp2[res2[++tpA2]];
	for(int i=1;i<=n;++i) rv1[o1[i]]=rv2[o2[i]]=i,res[i]=o1[i]|o2[i];
	for(int i=1,j=n+1,t=0;i<=n+1;++i)
	{
		while(j>1 && t>0) --j,t-=f1(i,j);if(i<=n) t+=f2(i,j);
		if(i>1 && j<=n && f1(i-1,j) && f2(i-1,j)) res[i-1]=j;
	}return res;
}
int main()
{
	scanf("%d",&n);a.resize(n+1);b.resize(n+1);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1,x;i<=n;++i) scanf("%d",&x),b[x]=i;
	ans=unitMongeMul(a,b);for(int i=1;i<=n;++i) printf("%d ",ans[i]);return 0;
}