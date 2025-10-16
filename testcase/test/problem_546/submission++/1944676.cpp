









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
map<int,vector<pair<int,int>>> X,Y;
map<pair<int,int>,int> Xid,Yid;
map<int,vector<int>> Add,Rmv;
vector<int> Xv,Yv;
int N;
void WorkX(){
	if(X.find(s.fi)==X.end()){
		X[s.fi]=vector<pair<int,int>>(0);
	}
	for(auto it=X.begin();it!=X.end();it++){
		if((it==X.begin() && it->fi>1) || (it!=X.begin() && prev(it)->fi!=it->fi-1)){
			Xid[{it->fi-1,m}]=++N;
			X[it->fi-1]=vector<pair<int,int>>(1,{1,m});
		}
		sort(all(it->se));
		vector<pair<int,int>> res;
		int lst=0;
		for(auto [x,y]:it->se){
			if(x!=lst+1){
				Xid[{it->fi,x-1}]=++N;
				res.push_back({lst+1,x-1});
			}
			lst=x;
		}
		if(lst!=m){
			Xid[{it->fi,m}]=++N;
			res.push_back({lst+1,m});
		}	
		swap(it->se,res);
	}
	if(X.empty() || X.rbegin()->fi!=n){
		Xid[{n,m}]=++N;
		X[n]=vector<pair<int,int>>(1,{1,m});
	}
	for(auto &[x,ls]:X){
		Xv.push_back(x);
	}
}
void WorkY(){
	if(Y.find(s.se)==Y.end()){
		Y[s.se]=vector<pair<int,int>>(0);
	}
	for(auto it=Y.begin();it!=Y.end();it++){
		if((it==Y.begin() && it->fi>1) || (it!=Y.begin() && prev(it)->fi!=it->fi-1)){
			Yid[{n,it->fi-1}]=++N;
			Add[0].push_back(N);
			Rmv[n+1].push_back(N);
			Y[it->fi-1]=vector<pair<int,int>>(1,{1,n});
		}
		sort(all(it->se));
		vector<pair<int,int>> res;
		int lst=0;
		for(auto [x,y]:it->se){
			if(x!=lst+1){
				Yid[{x-1,it->fi}]=++N;
				Add[lst].push_back(N);
				Rmv[x].push_back(N);
				res.push_back({lst+1,x-1});
			}
			lst=x;
		}
		if(lst!=n){
			Yid[{n,it->fi}]=++N;
			Add[lst].push_back(N);
			Rmv[n+1].push_back(N);
			res.push_back({lst+1,n});
		}	
		swap(it->se,res);
	}
	if(Y.empty() || Y.rbegin()->fi!=m){
		Yid[{n,m}]=++N;
		Add[0].push_back(N);
		Rmv[n+1].push_back(N);
		Y[m]=vector<pair<int,int>>(1,{1,n});
	}
	for(auto &[y,ls]:Y){
		Yv.push_back(y);
	}
}
int FindLessX(int x){
	int l=0,r=Xv.size()-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Xv[mid]<=x){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return Xv[ans];
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
	return Xv[ans];
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
	return Yv[ans];
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
	return Yv[ans];
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
	vector<int>* add=&Add[0];
	for(auto &[x,ls]:X){
		
		rt=NewP(rt,1);
		
		
		if(Rmv.find(x)!=Rmv.end()){
			for(auto id:Rmv[x]){
				
				Erase(rt,L,R,id);
			}
		}
		if(add!=nullptr){
			for(auto id:*add){
				
				Insert(rt,L,R,id);
			}
			add=nullptr;
		}
		BuildEdge(rt,L,R);
		
		for(auto [l,r]:ls){
			int id=Xid[{x,r}];
			int LF=FindBigY(l);
			int RF=FindLessY(r);
			int lf=Yid[{FindEle(Y[LF],x),LF}];
			int rf=Yid[{FindEle(Y[RF],x),RF}];
			
			
			
			
			AddEdge(rt,L,R,lf,rf,id);
			
		}
		
		if(Add.find(x)!=Add.end())	add=&Add[x];
		
	}
}
deque<int> q;
vector<int> dis;
vector<int> vis;
void BFS(){
	dis.resize(N+1);
	vis.resize(N+1);
	fill(all(dis),INT_MAX);
	int LF=FindBigX(s.fi);
	int RF=FindBigY(s.se);
	int lf=Xid[{LF,FindEle(X[LF],s.se)}];
	int rf=Yid[{FindEle(Y[RF],s.fi),RF}];
	dis[lf]=0,dis[rf]=0;
	q.push_front(lf);
	q.push_front(rf);
	while(!q.empty()){
		int u=q.front();
		q.pop_front();
		if(vis[u])	continue;
		vis[u]=1;
		for(int i=head[u];i;i=E[i].nxt){
			int v=E[i].v;
			int w=E[i].w;
			
			
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					if(w==0){
						q.push_front(v);
					}else{
						q.push_back(v);
					}
				}
			}
		}
	}
}
signed main(){
	n=RIN,m=RIN,k=RIN,qr=RIN;
	foru(i,1,k){
		p[i]={RIN,RIN};
		X[p[i].fi].push_back({p[i].se,0});
		Y[p[i].se].push_back({p[i].fi,0});
	}
	s={RIN,RIN};
	WorkX();
	
		
		
			
		
		
	
	WorkY();
	
		
		
			
		
		
	
	e.resize(N+1);
	L=Xid.size()+1,R=Xid.size()+Yid.size();
	BuildCross();
	
	
	BFS();
	while(qr--){
		pair<int,int> t={RIN,RIN};
		int LF=FindBigX(t.fi);
		int RF=FindBigY(t.se);
		int lf=Xid[{LF,FindEle(X[LF],t.se)}];
		int rf=Yid[{FindEle(Y[RF],t.fi),RF}];
		
		
		int ans=min(dis[lf],dis[rf]);
		printf("%d\n",ans==INT_MAX?-1:ans);
	}
	
	return 0;
}