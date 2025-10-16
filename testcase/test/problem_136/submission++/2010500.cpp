#include<cstdio>
#include<algorithm>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)

using std::sort;

const int N=1005,M=1e5+5;
int f[N],n,m,k;
struct edge{
	int u,v,w;
}ed[M];

bool operator<(edge a,edge b){
	return a.w<b.w;
}
int fd(int k){
	return f[k]==k?k:f[k]=fd(f[k]);
}
int main(){
	int ca,i,u,v;
	scanf("%d%d%d",&n,&m,&k);
	UP(i,1,m){
		scanf("%d%d%d",&ed[i].u,&ed[i].v,&ed[i].w);
	}
	sort(ed+1,ed+m+1);
	UP(ca,1,k){
		UP(i,1,n){
			f[i]=i;
		}
		scanf("%d%d",&u,&v);
		for(i=1;i<=m&&fd(u)!=fd(v);++i){
			f[fd(ed[i].u)]=fd(ed[i].v);
		}
		if(fd(u)!=fd(v)){
			printf("-1\n");
		}else{
			printf("%d\n",ed[i-1].w);
		}
	}
	return 0;
}