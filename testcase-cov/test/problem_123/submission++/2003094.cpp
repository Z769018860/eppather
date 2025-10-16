#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=1e6+10;
int n,m;
long long ans;
int fa[N];
struct stu
{
	int x,y,z;
}e[M];
bool cmp(stu a,stu b)
{
	return a.z<b.z;
}
int find(int x)
{
	return (x==fa[x])?x:fa[x]=find(fa[x]); 
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		e[i].x=x,e[i].y=y,e[i].z=z;
	}
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		int x=e[i].x,y=e[i].y,z=e[i].z;
		int fx=find(fa[x]),fy=find(fa[y]);
		if(fx!=fy)
		{
			fa[fx]=fy;
			ans+=z;
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}