#include <bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
using namespace std; using ull = unsigned long long;
mt19937_64 rng(190345);
template<int N>
class Treap{
	struct Node{
		Node *lc=0,*rc=0; int siz=0,val=0,id=0; ull pri=0;
		bool operator< (const Node& O) const { return val!=O.val?val<O.val:id<O.id; }
		void update() { siz=(lc?lc->siz:0)+(rc?rc->siz:0)+1; }
	};
	Node *rt,pool[N]; int pcnt;
	Node* Dummy(int x) { static Node qwq; qwq.val=x; return &qwq; }
	Node* newnode(int x){
		Node* u=&pool[++pcnt]; u->siz=1; u->val=x; u->pri=rng(); u->id=pcnt; return u;
	}
	void splitv(Node* u,Node* vl,Node*& x,Node*& y){
		if(!u) return x=y=0,void();
		if((*u)<(*vl)) x=u,splitv(x->rc,vl,x->rc,y),x->update();
		else y=u,splitv(y->lc,vl,x,y->lc),y->update();
	}
	void splits(Node* u,int sz,Node*& x,Node*& y){
		if(!u) return x=y=0,void();
		int s0=u->lc?u->lc->siz:0;
		if(s0<sz) x=u,splits(x->rc,sz-s0-1,x->rc,y),x->update();
		else y=u,splits(y->lc,sz,x,y->lc),y->update();
	}
	Node* merge(Node* x,Node* y){
		if(!x||!y) return x?x:y;; assert((*x)<(*y));
		if(x->pri<y->pri) return x->rc=merge(x->rc,y),x->update(),x;
		else return y->lc=merge(x,y->lc),y->update(),y;
	}
public:
	void insert(int x) { Node *u=newnode(x),*l,*r; splitv(rt,u,l,r); rt=merge(merge(l,u),r); }
	void erase(int x){
		Node *l,*m,*r; splitv(rt,Dummy(x),l,m); splits(m,1,m,r); rt=merge(l,r);
	}
	int rank(int x){
		Node *l,*r; splitv(rt,Dummy(x),l,r); int res=(l?l->siz:0)+1; rt=merge(l,r); return res;
	}
	int kth(int k){
		Node *l,*m,*r; splits(rt,k-1,l,m); splits(m,1,m,r);
		int res=m->val; rt=merge(merge(l,m),r); return res;
	}
	int prev(int x){
		Node *l,*m,*r; splitv(rt,Dummy(x),m,r); splits(m,m->siz-1,l,m); int res=m->val; rt=merge(merge(l,m),r); return res;
	}
	int next(int x){
		Node *l,*m,*r; splitv(rt,Dummy(x+1),l,m); splits(m,1,m,r); int res=m->val; rt=merge(merge(l,m),r); return res;
	}
};
Treap<100005> T;
int main(){
	int Q; cin>>Q; while(Q--){
		int op,x; cin>>op>>x;
		if(op==1) T.insert(x);
		else if(op==2) T.erase(x);
		else if(op==3) cout<<T.rank(x)<<'\n';
		else if(op==4) cout<<T.kth(x)<<'\n';
		else if(op==5) cout<<T.prev(x)<<'\n';
		else cout<<T.next(x)<<'\n';
	}
	return 0;
}