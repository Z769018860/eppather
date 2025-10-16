#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)

using std::sort;

const int N=1e5+5;
int n,m,d[N];
struct point{
	int x,y,z;
}a[N];
struct node{
	int sz,vl,pri;
	node *ls,*rs;
}t[N<<5],*root[N<<3],*tot=t;

bool operator<(point a,point b){
	return a.x<b.x;
}

void init_node(node *u){
	u->sz=1;
	u->pri=rand();
	u->ls=u->rs=t;
}
void push_up(node *u){
	u->sz=u->ls->sz+u->rs->sz+1;
}
void rtt(node *&f,bool l){
	node *u;
	if(l){
		u=f->rs;
		f->rs=u->ls;
		u->ls=f;
	}else{
		u=f->ls;
		f->ls=u->rs;
		u->rs=f;
	}
	push_up(f);
	push_up(u);
	f=u;
}
void insert(int k,node *&u){
	if(u==t){
		u=++tot;
		init_node(u);
		u->vl=k;
		return;
	}
	if(k<u->vl){
		insert(k,u->ls);
		if(u->ls->pri>u->pri){
			rtt(u,false);
		}
	}else{
		insert(k,u->rs);
		if(u->rs->pri>u->pri){
			rtt(u,true);
		}
	}
	push_up(u);
}
int rank(int k,node *u){
	if(u==t){
		return 0;
	}else if(k<u->vl){
		return rank(k,u->ls);
	}else{
		return rank(k,u->rs)+u->ls->sz+1;
	}
}

int ls(int p){
	return p<<1;
}
int rs(int p){
	return p<<1|1;
}
void add(int x,int y,int p=1,int l=1,int r=m){
	int mid=(l+r)>>1;
	insert(y,root[p]);
	if(l==r){
		return;
	}
	if(x<=mid){
		add(x,y,ls(p),l,mid);
	}else{
		add(x,y,rs(p),mid+1,r);
	}
}
int query(int x,int y,int k,int p=1,int l=1,int r=m){
	int mid=(l+r)>>1,res=0;
	if(x<=l&&r<=y){
		return rank(k,root[p]);
	}
	if(x<=mid){
		res+=query(x,y,k,ls(p),l,mid);
	}
	if(mid+1<=y){
		res+=query(x,y,k,rs(p),mid+1,r);
	}
	return res;
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	UP(i,1,m<<2){
		root[i]=t;
	}
	UP(i,1,n){
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	}
	sort(a+1,a+n+1);
	i=1;
	while(i<=n){
		j=i;
		while(j<n&&a[j].x==a[j+1].x){
			++j;
		}
		UP(k,i,j){
			add(a[k].y,a[k].z);
		}
		UP(k,i,j){
			int q=query(1,a[k].y,a[k].z)-1;
			++d[q];
		}
		i=j+1;
	}
	UP(i,1,n){
		printf("%d\n",d[i-1]);
	}
	return 0;
}