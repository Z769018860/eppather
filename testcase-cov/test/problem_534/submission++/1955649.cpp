#include<bits/stdc++.h>
using namespace std;
const int N=15005;
int q,V,T,ans,id[N],dp[N];
int g[21][N],ls[21],nw[21];
vector<pair<int,int> >e[N<<2];
void build(int k,int l,int r,int d){
	if(l==r){
		id[l]=k,dp[l]=d;
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid,d+1),build(k<<1|1,mid+1,r,d+1);
}
void modify(int k,int l,int r,int x,int y,pair<int,int>v){
	if(x<=l&&r<=y)return e[k].push_back(v),void();
	int mid=l+r>>1;
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(y>mid)modify(k<<1|1,mid+1,r,x,y,v);
}
void query(int x,int v){
	for(int k=id[x],d=dp[x];~d;--d,k>>=1)nw[d]=k;
	for(int i=0;i<=dp[x];++i){
		if(nw[i]!=ls[i])memcpy(g[i],g[i-1],sizeof(g[i]));
		for(auto v:e[nw[i]])for(int j=V;j>=v.first;--j)if(~g[i][j-v.first])g[i][j]=max(g[i][j],g[i][j-v.first]+v.second);
		e[nw[i]].clear();
		ls[i]=nw[i];
	}
	if(~g[dp[x]][v])printf("1 %d\n",ans=g[dp[x]][v]),ans^=1;
	else puts("0 0"),ans=0;
}
int main(){
	scanf("%d%d%d",&q,&V,&T);
	memset(g,-1,sizeof(g)),g[0][0]=0,ls[0]=1;
	build(1,1,q,0);
	for(int i=1,op,v,w,e;i<=q;++i){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&v,&w,&e);
			v-=T*ans,w-=T*ans,e-=T*ans;
			modify(1,1,q,i,e,make_pair(v,w));
		}else{
			scanf("%d",&v);
			v-=T*ans;
			query(i,v);
		}
	}
	return 0;
}