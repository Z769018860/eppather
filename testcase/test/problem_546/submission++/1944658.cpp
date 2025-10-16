#include<iostream>
#include<algorithm>
#define INF 2000000000
using namespace std;
int kd(){
	int x=0,f=1;
	char a=getchar();
	while(a<'0'||a>'9'){
		if(a=='-'){
			f=-1;
		}
		a=getchar();
	}
	while(a>='0'&&a<='9'){
		x=x*10+a-'0';
		a=getchar();
	}
	return x*f;
}
int n,m,k,q;
struct node{
	int x,y;
}a[50010];
bool cnp(node x,node y){
	return x.x==y.x?x.y<y.y:x.x<y.x;
}
bool chp(node x,node y){
	return x.y==y.y?x.x<y.x:x.y<y.y;
}
struct nod{
	int id;
	int zhi;
}b[50010];
bool cmp(nod x,nod y){
	return x.zhi<y.zhi;
}
struct nde{
	int l,r;
}tx[100010],ty[100010];
int cntx,cnty;
struct xx{
	int l,r;
	int x;
	int id;
}xian[200010];
bool cup(xx x,xx y){
	return x.l<y.l;
}
bool cxp(xx x,xx y){
	return x.x==y.x?x.l<y.l:x.x<y.x;
}
struct yy{
	int l,r;
	int y;
}heng[200010];
bool cyp(yy x,yy y){
	return x.y==y.y?x.l<y.l:x.y<y.y;
}
int cnt;
int duo;
struct neo{
	int to;
	int nxt;
	int val;
}edge[20000010];
int head[9000010],tot;
void addedge(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].nxt=head[u];
	edge[tot].val=w;
	head[u]=tot;
}
int wei[100010];
struct ndo{
	int l,r;
	int ls,rs;
}tree[4000010];
int zong=0;
void build(int i,int l,int r){
	tree[i].l=l;
	tree[i].r=r;
	if(l==r){
		if(wei[l]!=0){
			addedge((i+3*(k+1))*2-1,wei[l],0);
			addedge(wei[l],(i+3*(k+1))*2,0);
		}
		return ;
	}
	int mid=(l+r)/2;
	tree[i].ls=++zong;
	addedge((i+3*(k+1))*2-1,(zong+3*(k+1))*2-1,0);
	addedge((zong+3*(k+1))*2,(i+3*(k+1))*2,0);
	build(zong,l,mid);
	tree[i].rs=++zong;
	addedge((i+3*(k+1))*2-1,(zong+3*(k+1))*2-1,0);
	addedge((zong+3*(k+1))*2,(i+3*(k+1))*2,0);
	build(zong,mid+1,r);
}
void buil(int i,int j,int p,int u){
	tree[j]=tree[i];
	if(tree[j].l==tree[j].r){
		addedge((j+3*(k+1))*2-1,u,0);
		addedge(u,(j+3*(k+1))*2,0);
		return ;
	}
	if(tree[tree[i].ls].r>=p){
		tree[j].ls=++zong;
		addedge((j+3*(k+1))*2-1,(tree[j].ls+3*(k+1))*2-1,0);
		addedge((tree[j].ls+3*(k+1))*2,(j+3*(k+1))*2,0);
		addedge((j+3*(k+1))*2-1,(tree[j].rs+3*(k+1))*2-1,0);
		addedge((tree[j].rs+3*(k+1))*2,(j+3*(k+1))*2,0);
		buil(tree[i].ls,tree[j].ls,p,u);
	}
	else{
		tree[j].rs=++zong;
		addedge((j+3*(k+1))*2-1,(tree[j].ls+3*(k+1))*2-1,0);
		addedge((tree[j].ls+3*(k+1))*2,(j+3*(k+1))*2,0);
		addedge((j+3*(k+1))*2-1,(tree[j].rs+3*(k+1))*2-1,0);
		addedge((tree[j].rs+3*(k+1))*2,(j+3*(k+1))*2,0);
		buil(tree[i].rs,tree[j].rs,p,u);
	}
}
void search(int i,int l,int r,int u){
	if(tree[i].l>=l&&tree[i].r<=r){
		addedge(u,(i+3*(k+1))*2-1,1);
		addedge((i+3*(k+1))*2,u,1);
		return ;
	}
	if(tree[tree[i].ls].r>=l){
		search(tree[i].ls,l,r,u);
	}
	if(tree[tree[i].rs].l<=r){
		search(tree[i].rs,l,r,u);
	}
}
int dis[9000010];
pair<int,int> work(int x,int y){
	int l=1,r=cnt;
	while(l<r){
		int mid=(l+r)/2;
		if(xian[mid].x<x||(xian[mid].x==x&&xian[mid].r<y)){
			l=mid+1;
		}
		else{
			r=mid;
		}
	}
	int yi=xian[l].id;
	l=1,r=duo;
	while(l<r){
		int mid=(l+r)/2;
		if(heng[mid].y<y||(heng[mid].y==y&&heng[mid].r<x)){
			l=mid+1;
		} 
		else{
			r=mid;
		}
	}
	int er=l;
	return make_pair(yi,er);
}
int dui[18000010],he,ta;
bool vis[18000010];
void dij(){
	for(int i=1;i<=6*(k+1)+zong*2;i++){
		dis[i]=INF;
	}
	pair<int,int> tmp=work(a[0].x,a[0].y);
	dis[tmp.first]=0;
	dis[tmp.second+cnt]=0;
	he=9000000,ta=9000001;
	dui[9000000]=tmp.first;
	dui[9000001]=tmp.second+cnt;
	while(he<=ta){
		int u=dui[he];
		he++;
		if(vis[u]==1){
			continue;
		}
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(vis[v]==1){
				continue;
			}
			if(dis[v]>dis[u]+edge[i].val){
				dis[v]=dis[u]+edge[i].val;
				if(edge[i].val==0){
					he--;
					dui[he]=v;	
				}
				else{
					ta++;
					dui[ta]=v;
				}
			}
		}
	}
}
int main(){
	cin>>n>>m>>k>>q;
	for(int i=1;i<=k;i++){
		a[i].x=kd();a[i].y=kd();
	}
	a[0].x=kd();a[0].y=kd();
	for(int i=0;i<=k;i++){
		b[i].zhi=a[i].x;
		b[i].id=i; 
	}
	sort(b,b+k+1,cmp);
	for(int i=0;i<=k;i++){
		if(b[i].zhi>b[i-1].zhi+1){
			++cntx;
			tx[cntx].l=b[i-1].zhi+1;
			tx[cntx].r=b[i].zhi-1;
		}
		if(b[i].zhi>b[i-1].zhi){
			++cntx;
			tx[cntx].l=b[i].zhi;
			tx[cntx].r=b[i].zhi;
		}
		a[b[i].id].x=cntx;
	}
	if(n>b[k].zhi){
		++cntx;
		tx[cntx].l=b[k].zhi+1;
		tx[cntx].r=n;
	}
	for(int i=0;i<=k;i++){
		b[i].zhi=a[i].y;
		b[i].id=i;
	}
	sort(b,b+k+1,cmp);
	for(int i=0;i<=k;i++){
		if(b[i].zhi>b[i-1].zhi+1){
			++cnty;
			ty[cnty].l=b[i-1].zhi+1;
			ty[cnty].r=b[i].zhi-1;
		}
		if(b[i].zhi>b[i-1].zhi){
			++cnty;
			ty[cnty].l=b[i].zhi;
			ty[cnty].r=b[i].zhi;
		}
		a[b[i].id].y=cnty;
	}
	if(m>b[k].zhi){
		++cnty;
		ty[cnty].l=b[k].zhi+1;
		ty[cnty].r=m;
	}
	sort(a+1,a+k+1,cnp);
	int j=1;
	for(int i=1;i<=k;i++){
		while(j<=cntx&&j<a[i].x){
			++cnt;
			xian[cnt].l=1;
			xian[cnt].r=cnty;
			xian[cnt].x=j;
			j++;
		}
		if(i==1||a[i].x!=a[i-1].x){
			if(a[i].y>1){
				++cnt;
				xian[cnt].l=1;
				xian[cnt].r=a[i].y-1;
				xian[cnt].x=a[i].x;
			}
		}
		else{
			if(a[i-1].y+1<=a[i].y-1){
				++cnt;
				xian[cnt].l=a[i-1].y+1;
				xian[cnt].r=a[i].y-1;
				xian[cnt].x=a[i].x;
			}
		}
		if(i==k||a[i].x!=a[i+1].x){
			if(a[i].y<cnty){
				++cnt;
				xian[cnt].l=a[i].y+1;
				xian[cnt].r=cnty;
				xian[cnt].x=a[i].x;
			}
			j++;
		}
	}
	while(j<=cntx){
		++cnt;
		xian[cnt].l=1;
		xian[cnt].r=cnty;
		xian[cnt].x=j;
		j++;
	}
	sort(xian+1,xian+cnt+1,cup);
	for(int i=1;i<=cnt;i++){
		xian[i].id=i;
	}
	sort(a+1,a+k+1,chp);
	int h=1;
	while(xian[h].l==1){
		wei[xian[h].x]=h;
		h++;
	}
	zong=1;
	int tou=1;
	build(1,1,cntx);
	j=1;
	for(int i=1;i<=k;i++){
		while(j<=cnty&&j<a[i].y){
			++duo;
			heng[duo].l=1;
			heng[duo].r=cntx;
			heng[duo].y=j;
			search(tou,1,cntx,duo+cnt);
			j++;
			while(h<=cnt&&xian[h].l<=j){
				int cun=tou;
				tou=++zong;
				buil(cun,zong,xian[h].x,h);
				h++;
			}
		}
		if(i==1||a[i].y!=a[i-1].y){
			if(a[i].x!=1){
				++duo;
				heng[duo].l=1;
				heng[duo].r=a[i].x-1;
				heng[duo].y=j;
				search(tou,1,a[i].x-1,duo+cnt);
			}
		}
		else{
			if(a[i-1].x+1<=a[i].x-1){
				++duo;
				heng[duo].l=a[i-1].x+1;
				heng[duo].r=a[i].x-1;
				heng[duo].y=j;
				search(tou,a[i-1].x+1,a[i].x-1,duo+cnt);
			}
		}
		if(i==k||a[i].y!=a[i+1].y){
			if(a[i].x<cntx){
				++duo;
				heng[duo].l=a[i].x+1;
				heng[duo].r=cntx;
				heng[duo].y=j;
				search(tou,a[i].x+1,cntx,duo+cnt);
			}
			++j;
			while(h<=cnt&&xian[h].l<=j){
				int cun=tou;
				tou=++zong;
				buil(cun,zong,xian[h].x,h);
				h++;
			}
		}
	} 
	while(j<=cnty){
		++duo;
		heng[duo].l=1;
		heng[duo].r=cntx;
		heng[duo].y=j;
		search(tou,1,cntx,duo+cnt);
		j++;
	}
	sort(xian+1,xian+cnt+1,cxp);
	sort(heng+1,heng+duo+1,cyp);
	dij();
	while(q--){
		int x=kd(),y=kd();
		int l=1,r=cntx;
		while(l<r){
			int mid=(l+r)/2;
			if(tx[mid].r<x){
				l=mid+1;
			}
			else{
				r=mid;
			}
		}
		x=l;
		l=1,r=cnty;
		while(l<r){
			int mid=(l+r)/2;
			if(ty[mid].r<y){
				l=mid+1;
			}
			else{
				r=mid;
			}
		}
		y=l;
		pair<int,int> tmp=work(x,y);
		if(min(dis[tmp.first],dis[tmp.second+cnt])==INF){
			printf("-1\n");
		}
		else{
			printf("%d\n",min(dis[tmp.first],dis[tmp.second+cnt]));
		}
	}
	return 0;
}