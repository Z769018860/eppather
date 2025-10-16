#include<cstdio>
#include<iostream>
using namespace std;
const int N=1000,M=100000;
int fa[N],h[N],cnt,n,m,q,deep[N],f[N][14],d[N][14],x[M],y[M],z[M];
struct edge{
	int u,v,t;
}a[M<<1];
int re(){
	char c;
	int res=0;
	while((c=getchar())>'9'||c<'0');
	res+=c-'0';
	while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';
	return res;
}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void add(int x,int y,int z){a[++cnt].u=y,a[cnt].v=z,a[cnt].t=h[x],h[x]=cnt;}
void dfs(int x,int fat){
	deep[x]=deep[fat]+1;
	for(int i=1;i<14;i++)f[x][i]=f[f[x][i-1]][i-1],d[x][i]=max(d[x][i-1],d[f[x][i-1]][i-1]);
	for(int i=h[x];i;i=a[i].t){
		if(a[i].u==fat)continue;
		f[a[i].u][0]=x,d[a[i].u][0]=a[i].v;
		dfs(a[i].u,x); 
	}
}
int lca(int x,int y){
	int ans=0;
    if(deep[x]<deep[y])swap(x,y);
    for(int i=13;i>=0;i--){
        if(deep[f[x][i]]>=deep[y])ans=max(ans,d[x][i]),x=f[x][i];
        if(x==y)return ans;
    }
    for(int i=13;i>=0;i--)if(f[x][i]!=f[y][i])ans=max(ans,max(d[x][i],d[y][i])),x=f[x][i],y=f[y][i];
    ans=max(ans,d[x][0]),ans=max(ans,d[y][0]);
    return ans;
}
void qsort(int l,int r){
	int i=l,j=r,mid=z[l+r>>1];
	while(i<=j){
		while(z[i]<mid)i++;
		while(z[j]>mid)j--;
		if(i<=j){
			swap(x[i],x[j]);
			swap(y[i],y[j]);
			swap(z[i],z[j]);
			i++,j--;
		}
	}
	if(l<j)qsort(l,j);
	if(i<r)qsort(i,r);
}
int main(){
	n=re(),m=re(),q=re();
	for(int i=0;i<n;i++)fa[i]=i;
	for(int i=0;i<m;i++)x[i]=re()-1,y[i]=re()-1,z[i]=re();
	qsort(0,m-1);
	for(int i=0;i<m;i++){
		int afa=find(x[i]),bfa=find(y[i]);
		if(afa!=bfa){
			add(x[i],y[i],z[i]);
			add(y[i],x[i],z[i]);
			fa[afa]=bfa;
		}
	}
	for(int i=0;i<n;i++)if(deep[i]==0)dfs(i,n);
	while(q--){
		int x=re()-1,y=re()-1;
		if(find(x)!=find(y)){
			puts("-1");
			continue;
		}
		printf("%d\n",lca(x,y));
	}
}