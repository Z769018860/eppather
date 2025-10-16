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
mt19937_64 myrand(1145);
namespace Treap{
	struct Node{
		Node *l,*r;
		int siz,val;
		ull wei;
		bool flag;
		Node(int value=0)
		{
			l=r=nullptr;siz=1;val=value;wei=myrand();flag=false;
		}
		void update()
		{
			siz=1;
			if(l!=nullptr)siz+=l->siz;
			if(r!=nullptr)siz+=r->siz;
		}
		void pushdown()
		{
			if(flag)
			{
				if(l!=nullptr)
				{
					swap(l->l,l->r);l->flag=!l->flag;
				}
				if(r!=nullptr)
				{
					swap(r->l,r->r);r->flag=!r->flag;
				}
				flag=false;
			}
		}
	};
	pair<Node*,Node*> split(Node* tr,int rk)
	{
		if(tr==nullptr) return mp(nullptr,nullptr);
		tr->pushdown();
		if((tr->l==nullptr?0:tr->l->siz)>=rk)
		{
			pair<Node*,Node*> Q=split(tr->l,rk);
			tr->l=Q.se;tr->update();
			return mp(Q.fi,tr);
		}
		pair<Node*,Node*> Q=split(tr->r,rk-(tr->l==nullptr?0:tr->l->siz)-1);
		tr->r=Q.fi;tr->update();
		return mp(tr,Q.se);
	}
	Node* merge(Node *p, Node *q)
	{
		if(p==nullptr) return q;
		if(q==nullptr) return p;
		p->pushdown();q->pushdown();
		if(p->wei<q->wei)
		{
			p->r=merge(p->r,q);p->update();
			return p;
		}
		q->l=merge(p,q->l);q->update();
		return q;
	}
	void fingerprint(Node *tr,int tab=0)
	{
		for(int i=0;i<tab;++i) cout<<"\t";
		if(tr==nullptr)
		{
			cout<<"Null\n";return ;
		}
		cout<<"Tree Root: "<<tr->val<<endl;
		cout<<"L\n";
		fingerprint(tr->l,tab+1);
		cout<<"R\n";
		fingerprint(tr->r,tab+1);
		cout<<"End"<<endl; 
	}
	void printtree(Node *tr)
	{
		if(tr==nullptr) return ;
		tr->pushdown();
		printtree(tr->l);cout<<(tr->val)<<' ';printtree(tr->r);
	}
	struct treap{
		Node *rt;
		treap()
		{
			rt=nullptr;
		}
		void build(int n)
		{
			Node *M;
			for(int i=1;i<=n;++i)
			{
				M=new Node(i);
				rt=merge(rt,M);
			}
		}
		void reverse(int l,int r)
		{
			pair<Node*,Node*> L=split(rt,l-1);
		
		
			pair<Node*,Node*> R=split(L.se,r-l+1);
			if(R.fi!=nullptr)
			{
				swap(R.fi->l,R.fi->r);R.fi->flag=!R.fi->flag;
			}
		
		
		
		
		
		
		
			rt=merge(L.fi,merge(R.fi,R.se));
		
		
		}
		void print()
		{
			printtree(rt);
		}
	};
}
Treap::treap Q;
int n,q,l,r;
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>q;
	Q.build(n);
	while(q--)
	{
		cin>>l>>r;Q.reverse(l,r);
	}
	Q.print();
	return 0;
}