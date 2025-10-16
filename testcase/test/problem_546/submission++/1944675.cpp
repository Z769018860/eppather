










#include <bits/extc++.h>
#define INF 0x7fffffff
#define MAXN 50005
#define eps 1e-9
#define foru(a,b,c)	for(int a=b;a<=c;a++)
#define RT return 0;
#define LL long long
#define LXF int
#define RIN rin()
#define HH printf("\n")
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
inline LXF rin(){
	LXF x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){ 
	if(ch=='-') w=-1;
	ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
	x=x*10+(ch-'0');
	ch=getchar();
	}
	return x*w;
}
int n,m;
int k;
int qr;
pair<int,int> p[MAXN],s;
vector<pair<int,int>> X[MAXN*3];
vector<pair<int,int>> Y[MAXN*3];
map<pair<int,int>,int> Xid,Yid;
vector<int> Add[MAXN*3];
vector<int> Rmv[MAXN*3];
vector<int> Xv,Yv;
unordered_map<int,int> dx,dy;
int rdx[MAXN*3],rdy[MAXN*3];
int N;
void WorkX(){
	for(int i=0;i<Xv.size();i++){
		vector<pair<int,int>> res;
		int lst=-1;
		sort(all(X[i]));
		for(auto [x,y]:X[i]){
			if(x!=lst+1){
				Xid[{i,x-1}]=++N;
				res.push_back({lst+1,x-1});
			}
			lst=x;
		}
		if(lst!=Yv.size()-1){
			Xid[{i,Yv.size()-1}]=++N;
			res.push_back({lst+1,Yv.size()-1});
		}
		swap(X[i],res);
	}
}
void WorkY(){
	for(int i=0;i<Yv.size();i++){
		vector<pair<int,int>> res;
		int lst=-1;
		sort(all(Y[i]));
		for(auto [x,y]:Y[i]){
			
			if(x!=lst+1){
				Yid[{x-1,i}]=++N;
				Add[lst].push_back(N);
				Rmv[x].push_back(N);
				res.push_back({lst+1,x-1});
			}
			lst=x;
		}
		
		if(lst!=Xv.size()-1){
			Yid[{Xv.size()-1,i}]=++N;
			Add[lst].push_back(N);
			Rmv[Xv.size()].push_back(N);
			res.push_back({lst+1,Xv.size()-1});
		}
		swap(Y[i],res);
	}
}
int FindBigX(int x){
	int l=0,r=Xv.size()-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Xv[mid]>=x){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	return ans;
}
int FindBigY(int x){
	int l=0,r=Yv.size()-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Yv[mid]>=x){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	return ans;
}
int FindLessY(int x){
	int l=0,r=Yv.size()-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Yv[mid]<=x){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return ans;
}
int FindEle(vector<pair<int,int>>& ls,int x){
	
	
		
	
	
	int l=0,r=ls.size()-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ls[mid].fi<=x && x<=ls[mid].se)	return ls[mid].se;
		if(ls[mid].se<x){
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	exit(1);
}
vector<vector<pair<int,int>>> e;
class Edge{
	public:
		int v,w,nxt;
}E[MAXN*200];
int ecnt,head[MAXN*100];
void add_e(int u,int v,int w){
	
	E[++ecnt]={v,w,head[u]};
	head[u]=ecnt;
}
class SegTree{
	public:
		int in,out;
		int lc,rc;
		int bl;
}tr[MAXN*100];
int pcnt,rt;
int L,R;
int NewP(int p,bool isrt){
	pcnt++;
	tr[pcnt]={++N,++N,tr[p].lc,tr[p].rc,isrt?pcnt:rt};
	
	
	
	
	
	return pcnt;
}
void BuildEdge(int p,int l,int r){
	if(l==r){
		
		add_e(tr[p].out,l,0);
		
		
		add_e(l,tr[p].in,0);
		
		return ;
	}
	int mid=(l+r)>>1;
	if(tr[p].lc){
		if(tr[tr[p].lc].bl==tr[p].bl)	BuildEdge(tr[p].lc,l,mid);
		
		add_e(tr[tr[p].lc].in,tr[p].in,0);
		
		
		add_e(tr[p].out,tr[tr[p].lc].out,0);
		
	}
	if(tr[p].rc){
		if(tr[tr[p].rc].bl==tr[p].bl)	BuildEdge(tr[p].rc,mid+1,r);
		
		add_e(tr[tr[p].rc].in,tr[p].in,0);
		
		
		add_e(tr[p].out,tr[tr[p].rc].out,0);
		
	}
}
bool Erase(int &p,int l,int r,int pos){
	if(l==r)	return true;
	if(tr[p].bl!=rt){
		p=NewP(p,0);
		
		
	}
	int mid=(l+r)>>1;
	bool ret=0;
	if(pos<=mid){
		ret=(tr[p].lc!=0)&Erase(tr[p].lc,l,mid,pos);
		if(ret)	tr[p].lc=0;
		ret=(ret|(tr[p].lc==0))&(tr[p].rc==0);
	}else{
		ret=(tr[p].rc!=0)&Erase(tr[p].rc,mid+1,r,pos);
		if(ret)	tr[p].rc=0;
		ret=(ret|(tr[p].rc==0))&(tr[p].lc==0);
	}
	return ret;
}
void Insert(int &p,int l,int r,int pos){
	if(tr[p].bl!=rt){
		p=NewP(p,0);
		
		
	}
	if(l==r)	return ;
	int mid=(l+r)>>1;
	if(pos<=mid)	Insert(tr[p].lc,l,mid,pos);
	else	Insert(tr[p].rc,mid+1,r,pos);
}
void AddEdge(int p,int l,int r,int nl,int nr,int to){
	
	if(nl<=l && r<=nr){
		
		add_e(to,tr[p].out,1);
		
		
		add_e(tr[p].in,to,1);
		
		return ;
	}
	int mid=(l+r)>>1;
	if(nl<=mid && tr[p].lc)	AddEdge(tr[p].lc,l,mid,nl,nr,to);
	if(nr>mid && tr[p].rc)	AddEdge(tr[p].rc,mid+1,r,nl,nr,to);
}
void BuildCross(){
	for(int i=0;i<Xv.size();i++){
		
		rt=NewP(rt,1);
		
		
		for(auto id:Rmv[i]){
			
			Erase(rt,L,R,id);
		}
		for(auto id:Add[i-1]){
			
			Insert(rt,L,R,id);
		}
		BuildEdge(rt,L,R);
		
		for(auto [l,r]:X[i]){
			int id=Xid[{i,r}];
			int lf=Yid[{FindEle(Y[l],i),l}];
			int rf=Yid[{FindEle(Y[r],i),r}];
			
			
			
			
			AddEdge(rt,L,R,lf,rf,id);
			
		}
		
	}
}
int q[40000000],he=2e7,tl=2e7;

vector<int> dis;
vector<int> vis;
void BFS(){
	dis.resize(N+1);
	vis.resize(N+1);
	fill(all(dis),INT_MAX);
	int lf=Xid[{s.fi,FindEle(X[s.fi],s.se)}];
	int rf=Yid[{FindEle(Y[s.se],s.fi),s.se}];
	dis[lf]=0,dis[rf]=0;
	
	
	q[he++]=lf;
	q[he++]=rf;
	while(he>tl){
		
		
		int u=q[--he];
		if(vis[u])	continue;
		vis[u]=1;
		for(int i=head[u];i;i=E[i].nxt){
			int v=E[i].v;
			int w=E[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					if(w==0){
						q[he++]=v;
						
					}else{
						q[--tl]=v;
						
					}
				}
			}
		}
	}
}
void dowork(){
	int tmp;
	
	sort(all(Xv));
	Xv.erase(unique(all(Xv)),Xv.end());
	tmp=Xv.size();
	for(int i=0;i<tmp;i++){
		if((i==0 && Xv[i]>1) || (i!=0 && Xv[i]-1>Xv[i-1]))	Xv.push_back(Xv[i]-1);
	}
	sort(all(Xv));
	Xv.erase(unique(all(Xv)),Xv.end());
	for(int i=0;i<Xv.size();i++){
		dx[Xv[i]]=i;
		rdx[i]=Xv[i];
	}
	
	sort(all(Yv));
	Yv.erase(unique(all(Yv)),Yv.end());
	tmp=Yv.size();
	for(int i=0;i<tmp;i++){
		if((i==0 && Yv[i]>1) || (i!=0 && Yv[i]-1>Yv[i-1]))	Yv.push_back(Yv[i]-1);
	}
	sort(all(Yv));
	Yv.erase(unique(all(Yv)),Yv.end());
	for(int i=0;i<Yv.size();i++){
		dy[Yv[i]]=i;
		rdy[i]=Yv[i];
	}
}
signed main(){
	   
	   
	n=RIN,m=RIN,k=RIN,qr=RIN;
	foru(i,1,k){
		p[i]={RIN,RIN};
		Xv.push_back(p[i].fi);
		Yv.push_back(p[i].se);
	}
	s={RIN,RIN};
	Xv.push_back(s.fi);
	Xv.push_back(n);
	Yv.push_back(s.se);
	Yv.push_back(m);
	dowork();
	s.fi=dx[s.fi];
	s.se=dy[s.se];
	foru(i,1,k){
		X[dx[p[i].fi]].push_back({dy[p[i].se],0});
		Y[dy[p[i].se]].push_back({dx[p[i].fi],0});
	}
	WorkX();
	
		
		
			
		
		
	
	WorkY();
	
		
		
			
		
		
	
	
	e.resize(N+1);
	L=Xid.size()+1,R=Xid.size()+Yid.size();
	
	BuildCross();
	 
	BFS();
	 
	while(qr--){
		pair<int,int> t={RIN,RIN};
		t.fi=FindBigX(t.fi);
		t.se=FindBigY(t.se);
		int lf=Xid[{t.fi,FindEle(X[t.fi],t.se)}];
		int rf=Yid[{FindEle(Y[t.se],t.fi),t.se}];
		
		
		int ans=min(dis[lf],dis[rf]);
		printf("%d\n",ans==INT_MAX?-1:ans);
	}
	
	return 0;
}
