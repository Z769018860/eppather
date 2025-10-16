#include<cstdio>
#include<cstdlib>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)


const int N=3e5+5;
int n;
struct node{
	int sz,vl,pri;
	node *ls,*rs;
}t[N],*root=t,*tot=t;

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
void insert(int k,node *&u=root){
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
void erase(int k,node *&u=root){
	if(k==u->vl){
		if(u->ls==t){
			u=u->rs;return;
		}else if(u->rs==t){
			u=u->ls;return;
		}else if(u->ls->pri>u->rs->pri){
			rtt(u,false);
			erase(k,u->rs);
		}else{
			rtt(u,true);
			erase(k,u->ls);
		}
	}else if(k<u->vl){
		erase(k,u->ls);
	}else{
		erase(k,u->rs);
	}
	push_up(u);
}
int kth(int k,node *u=root){
	if(!k||k>u->sz){
		return -1;
	}
	if(k==u->ls->sz+1){
		return u->vl;
	}else if(k<u->ls->sz+1){
		return kth(k,u->ls);
	}else{
		return kth(k-u->ls->sz-1,u->rs);
	}
}
int rank(int k,node *u=root){
	if(u==t){
		return 0;
	}else if(k<=u->vl){
		return rank(k,u->ls);
	}else{
		return rank(k,u->rs)+u->ls->sz+1;
	}
}
int pre(int k){
	return kth(rank(k));
}
int suc(int k){
	return kth(rank(k+1)+1);
}
int main(){
	int i,o,k;
	init_node(t);t->sz=0;
	scanf("%d",&n);
	UP(i,1,n){
		scanf("%d%d",&o,&k);
		switch(o){
			case 0:insert(k);break;
			case 1:erase(k);break;
			case 2:printf("%d\n",kth(k));break;
			case 3:printf("%d\n",rank(k));break;
			case 4:printf("%d\n",pre(k));break;
			case 5:printf("%d\n",suc(k));break;
		}
	}
	return 0;
}