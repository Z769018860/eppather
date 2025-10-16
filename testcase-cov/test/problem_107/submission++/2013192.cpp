#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using namespace std;
unsigned time_related_rand()
{
	return unsigned(std::chrono::steady_clock::now().time_since_epoch().count());
}
mt19937_64 myrand(time_related_rand());
namespace Treap{
	struct Node{
		Node *l,*r;
		int cnt,siz,val;
		ull wei;
		Node(int value=0)
		{
			l=r=nullptr;cnt=siz=1;val=value;wei=myrand();
		}
		void update()
		{
			siz=cnt;
			if(l!=nullptr)siz+=l->siz;
			if(r!=nullptr)siz+=r->siz;
		}
	};
	pair<Node*,Node*> split(Node* tr,int val)
	{
		if(tr==nullptr) return mp(nullptr,nullptr);
		if((tr->val)<=val)
		{
			pair<Node*,Node*> Q=split(tr->r,val);
			tr->r=Q.fi;tr->update();
			return mp(tr,Q.se);
		}
		pair<Node*,Node*> Q=split(tr->l,val);
		tr->l=Q.se;tr->update();
		return mp(Q.fi,tr);
	}
	tuple<Node*,Node*,Node*> split3(Node* tr,int rk)
	{
		if(tr==nullptr) return make_tuple(nullptr,nullptr,nullptr);
		int L=((tr->l)==nullptr)?(0):(tr->l->siz);
		if(rk<=L)
		{
			Node *l,*m,*r;
			tie(l,m,r)=split3(tr->l,rk);
			tr->l=r;tr->update();return make_tuple(l,m,tr);
		}
		if(rk<=L+(tr->cnt))
		{
			Node *l=tr->l,*r=tr->r;tr->l=tr->r=nullptr;tr->update();
			return make_tuple(l,tr,r);
		}
		Node *l,*m,*r;
		tie(l,m,r)=split3(tr->r,rk-L-(tr->cnt));
		tr->r=l;tr->update();return make_tuple(tr,m,r);
	}
	Node* merge(Node *p, Node *q)
	{
		if(p==nullptr) return q;
		if(q==nullptr) return p;
		if(p->wei<q->wei)
		{
			p->r=merge(p->r,q);p->update();
			return p;
		}
		q->l=merge(p,q->l);q->update();
		return q;
	}
	struct treap{
		Node *rt;
		treap()
		{
			rt=nullptr;
		}
		void insert(int val)
		{
			pair<Node*,Node*> p=split(rt,val);
			pair<Node*,Node*> q=split(p.fi,val-1);
			Node *M;
			if(q.se==nullptr)
			{
				M=new Node(val);
			}
			else
			{
				M=q.se;++M->cnt;M->update();
			}
			rt=merge(merge(q.fi,M),p.se);
		}
		void erase(int val)
		{
			pair<Node*,Node*> p=split(rt,val);
			pair<Node*,Node*> q=split(p.fi,val-1);
			if(q.se->cnt==1)
			{
				delete q.se;
				rt=merge(q.fi,p.se);
				return ;
			}
			--q.se->cnt;q.se->update();
			rt=merge(merge(q.fi,q.se),p.se);
		}
		int rank(int val)
		{
			pair<Node*,Node*> p=split(rt,val-1);
			int ret=(p.fi==nullptr)?0:(p.fi->siz);
			rt=merge(p.fi,p.se);
			return ++ret;
		}
		int kth(int rk)
		{
			if(rk<=0||rk>(rt->siz)) return -1;
			Node *l,*m,*r;
			tie(l,m,r)=split3(rt,rk);
			int ret=m->val;
			rt=merge(l,merge(m,r));
			return ret;
		}
		int prev(int val)
		{
			return kth(rank(val)-1);
		}
		int next(int val)
		{
			return kth(rank(val+1));
		}
	};
}
Treap::treap Q;
int q,op,x;
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>q;
	while(q--)
	{
		cin>>op>>x;
		switch(op)
		{
			case 0:
				Q.insert(x);break;
			case 1:
				Q.erase(x);break;
			case 2:
				cout<<Q.kth(x)<<endl;break;
			case 3:
				cout<<Q.rank(x)-1<<endl;break;
			case 4:
				cout<<Q.prev(x)<<endl;break;
			case 5:
				cout<<Q.next(x)<<endl;break;
		}
	}
}