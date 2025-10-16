#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define N 100005
namespace IO{
	inline char nc(){
		static char buf[1000000],*p=buf,*q=buf;
		return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
	}
	inline int read(){
		int res = 0;
		char c = nc();
		while(c<'0'||c>'9')c=nc();
		while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
		return res;
	}
	char obuf[1<<21],*p3=obuf; 
	inline void pc(char c){ 
		p3-obuf<=(1<<20)?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c); 
	} 
	inline void write(long long x){ 
		if(x<0) pc('-'),x=-x; 
		if(x>9) write(x/10); 
		pc(x%10+'0'); 
	}
}
using namespace std;
using namespace IO;
using namespace __gnu_pbds;
struct node{
	int la[N],ne[N],to[N],w[N],tot;
	inline void merge(int x,int y,int z){tot++,ne[tot]=la[x],la[x]=tot,to[tot]=y,w[tot]=z;}
}treee;
int n,q,x,y,z,i,dfn_tot;
int dep_w[N],top[N],son[N],sum[N],fath[N],dfn[N],endd[N],ot[N],nid[N],work1[N],work2[N],siz[N];
long long ANS;
void dfs1(int x){
	sum[x] = 1;
	for(int i=treee.la[x];i;i=treee.ne[i]){
		dep_w[treee.to[i]] = dep_w[x] + treee.w[i],fath[treee.to[i]] = x;
		dfs1(treee.to[i]);
		sum[x] += sum[treee.to[i]];
		if(sum[treee.to[i]]>sum[son[x]]) son[x]=treee.to[i];
	}
}
void dfs2(int x,int r){
	top[x] = r,dfn[x] = ++dfn_tot,nid[dfn_tot] = x,siz[r]++;
	if(son[x]) dfs2(son[x],r),endd[x] = endd[son[x]];
	else endd[x] = x;
	for(int i=treee.la[x];i;i=treee.ne[i]){
		if(treee.to[i]==son[x]) continue;
		dfs2(treee.to[i],treee.to[i]);
	}
	ot[x] = dfn_tot;
}
struct cmp{bool operator()(int a,int b){return a>b;}};
priority_queue<int> s[2][N];
struct ppp{int first,second;}c;
bool operator<(ppp a,ppp b){return a.first<b.first;}
struct cmp2{bool operator()(ppp a,ppp b){return a.first>b.first;}};
tree<ppp,null_type,cmp2,rb_tree_tag,tree_order_statistics_node_update> op[N];
int tr[N<<2],ls[N<<2],rs[N<<2],tag[N<<2],tr_tot,root[N],pos[N];
ppp pai[2][N<<2];
ppp emp = (ppp){INT_MIN,-1};
inline void build(int s,int t,int p){
	pai[0][p] = pai[1][p] = emp;
	if(s==t){
		pos[s] = p;
		return ;
	}
	build(s,(s+t)>>1,p<<1),build(((s+t)>>1)+1,t,(p<<1)+1);
}
inline void build2(int s,int t,int &p){
	p = ++tr_tot;
	if(s==t) return ;
	build2(s,(s+t)>>1,ls[p]),build2(((s+t)>>1)+1,t,rs[p]);
}
inline void modify_delta(int l,int r,int c,int s,int t,int p){
	if(l<=s&&t<=r){
		tr[p] += c,tag[p] += c;
		return ;
	}
	if(tag[p]) tr[ls[p]]+=tag[p],tag[ls[p]]+=tag[p],tr[rs[p]]+=tag[p],tag[rs[p]]+=tag[p],tag[p]=0;
	if(l<=((s+t)>>1)) modify_delta(l,r,c,s,(s+t)>>1,ls[p]);
	if(r>((s+t)>>1)) modify_delta(l,r,c,((s+t)>>1)+1,t,rs[p]);
	tr[p]=min(tr[ls[p]],tr[rs[p]]);
}
inline void add(int x,int y,int s,int t,int p){
	p = pos[x],pai[y][p] = c;
	while(p>>1) p>>=1,pai[y][p] = max(pai[y][p<<1],pai[y][(p<<1)+1]);
}
inline int query1(int l,int r,int s,int t,int p){
	if(tr[p]>=1||l>t||r<s) return -1;
	if(s==t) return s;
	if(tag[p]) tr[ls[p]]+=tag[p],tag[ls[p]]+=tag[p],tr[rs[p]]+=tag[p],tag[rs[p]]+=tag[p],tag[p]=0;
	int ans = query1(l,r,s,(s+t)>>1,ls[p]);
	if(ans!=-1) return ans;
	return query1(l,r,((s+t)>>1)+1,t,rs[p]);
}
inline int query2(int l,int r,int s,int t,int p){
	if(tr[p]>=0||l>t||r<s) return -1;
	if(s==t) return s;
	if(tag[p]) tr[ls[p]]+=tag[p],tag[ls[p]]+=tag[p],tr[rs[p]]+=tag[p],tag[rs[p]]+=tag[p],tag[p]=0;
	int ans = query2(l,r,((s+t)>>1)+1,t,rs[p]);
	if(ans!=-1) return ans;
	return query2(l,r,s,(s+t)>>1,ls[p]);
}
inline void update(int k,int c){while(k) modify_delta(1,dfn[k]-dfn[top[k]]+1,c,1,siz[top[k]],root[top[k]]),k=fath[top[k]];}
inline ppp query(int l,int r,int c,int s,int t,int p){
	if(l<=s&&t<=r) return pai[c][p];
	if(l<=((s+t)>>1)&&r>((s+t)>>1)) return max(query(l,r,c,s,(s+t)>>1,p<<1),query(l,r,c,((s+t)>>1)+1,t,(p<<1)+1));
	else if(l<=((s+t)>>1)) return query(l,r,c,s,(s+t)>>1,p<<1);
	else return query(l,r,c,((s+t)>>1)+1,t,(p<<1)+1);
}
inline ppp found_pair_max(int k){
	if(op[k].size()==0) return emp;
	else return *op[k].begin();
}
inline int found_val_max(int p,int k){
	if(s[p][k].size()==0) return INT_MIN;
	else return s[p][k].top();
}
inline ppp found_list_max(int k){
	int pos = query1(dfn[k]-dfn[top[k]]+1,dfn[endd[k]]-dfn[top[k]]+1,1,siz[top[k]],root[top[k]]);
	if(pos==-1) pos=dfn[endd[k]]+1;
	else pos=pos+dfn[top[k]]-1;
	if(dfn[k]<=pos-1) return query(dfn[k],pos-1,0,1,n,1);
	else return emp;
}
inline void add_upd(int k){
	while(k){
		c = found_pair_max(k);
		add(dfn[k],0,1,n,1);
		if(fath[top[k]]) op[fath[top[k]]].insert(found_list_max(top[k]));
		k=fath[top[k]];
	}
}
inline void del_upd(int k){
	while(k){
		if(fath[top[k]]) op[fath[top[k]]].erase(found_list_max(top[k]));
		c = emp;
		add(dfn[k],0,1,n,1);
		k=fath[top[k]];
	}
}
inline void insert(int p,int x,int y){
	if(!p) del_upd(x);
	s[p][x].push(y);
	if(p==1) c=(ppp){found_val_max(p,x),x},add(dfn[x],p,1,n,1);
	else op[x].insert((ppp){y,x}),add_upd(x);
}
inline void chose(int p,int x){
	if(!p) del_upd(x);
	int val = found_val_max(p,x);
	ANS += val,s[p][x].pop();
	if(!p){
		op[x].erase((ppp){val,x});
		insert(1,x,-val),update(x,-1);
	}
	else{
		c=(ppp){found_val_max(p,x),x},add(dfn[x],1,1,n,1);
		insert(0,x,-val),del_upd(x),update(x,1),add_upd(x);
	}
	if(!p) add_upd(x);
}
inline void add_work(int u,int c){
	insert(0,u,c);
	if(found_val_max(0,u)!=c) return ;
	chose(0,u);
	while(u){
		int pos = query2(1,dfn[u]-dfn[top[u]]+1,1,siz[top[u]],root[top[u]]);
		if(pos!=-1){
			pos = nid[pos+dfn[top[u]]-1];
			chose(1,query(dfn[pos],ot[pos],1,1,n,1).second);
			return ;
		}
		u = fath[top[u]];
	}
}
inline void add_gold(int u,int c){
	insert(1,u,c);
	if(found_val_max(1,u)!=c) return ;
	chose(1,u),chose(0,found_list_max(1).second);
}
int main(){
	n=read(),q=read();
	for(i=1;i<n;i++) x=read(),y=read(),z=read(),treee.merge(x,y,z);
	dfs1(1),dfs2(1,1);
	for(i=1;i<=n;i++) if(top[i]==i) build2(1,siz[i],root[i]);
	build(1,n,1);
	while(q--){
		x=read(),y=read(),z=read();
		if(x==1) z-=dep_w[y],add_work(y,z);
		else z+=dep_w[y],add_gold(y,z);
		write(ANS),pc('\n');
	}
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
} 
