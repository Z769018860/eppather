#include<cstdio>
template<typename Tp>inline void swap(Tp&a,Tp&b){const Tp c=a;a=b,b=c;}
class LinkCutTree
{
	private:
		struct Node{unsigned int parent,child[2],value,xorsum,rev;}*node=nullptr;
		inline bool isroot(unsigned int x){return x!=node[node[x].parent].child[0]&&x!=node[node[x].parent].child[1];}
		inline void pushup(unsigned int x){node[x].xorsum=node[x].value^node[node[x].child[0]].xorsum^node[node[x].child[1]].xorsum;}
		inline void pushdown(unsigned int x){if(node[x].rev)swap(node[x].child[0],node[x].child[1]),node[node[x].child[0]].rev^=1,node[node[x].child[1]].rev^=1,node[x].rev=0;}
		inline void update(unsigned int x){
			if(!isroot(x))update(node[x].parent);
			pushdown(x);
		}
		inline void rotate(unsigned int x){
			unsigned int y=node[x].parent,z=node[y].parent,k=x==node[y].child[1];
			if(!isroot(y))node[z].child[y==node[z].child[1]]=x;
			node[y].child[k]=node[x].child[!k],node[node[x].child[!k]].parent=y,
			node[x].child[!k]=y,node[y].parent=x,node[x].parent=z,
			pushup(y),pushup(x);
		}
		inline void splay(unsigned int x){
			update(x);
			for(unsigned int y;y=node[x].parent,!isroot(x);rotate(x))
			if(!isroot(y))rotate((y==node[node[y].parent].child[1])==(x==node[node[x].parent].child[1])?y:x);
		}
		inline void access(unsigned int x){for(unsigned int y=0;x;y=x,x=node[x].parent)splay(x),node[x].child[1]=y,pushup(x);}
		inline void makeroot(unsigned int x){access(x),splay(x),node[x].rev^=1;}
	public:
		LinkCutTree(unsigned int size){node=new Node[size+1]();}
		~LinkCutTree(){delete[]node,node=nullptr;}
		inline void set(unsigned int x,unsigned int v){node[x].value=v;}
		inline unsigned int query(unsigned int x){return node[x].xorsum;}
		inline void modify(unsigned int x,unsigned int y){access(x),splay(x),node[x].value=y,pushup(x);}
		inline unsigned int find(unsigned int x){
			access(x),splay(x),pushdown(x);
			while(node[x].child[0])x=node[x].child[0],pushdown(x);
			return splay(x),x;
		}
		inline void split(unsigned int x,unsigned int y){makeroot(x),access(y),splay(y);}
		inline void link(unsigned int x,unsigned int y){makeroot(x),node[x].parent=y;}
		inline void cut(unsigned int x,unsigned int y){
			split(x,y);
			if(x==node[y].child[0]&&!node[x].child[1])node[y].child[0]=0,node[x].parent=0;
		}
};
int main()
{
	unsigned int n,m;
	scanf("%u%u",&n,&m);
	LinkCutTree tree(n);
	for(unsigned int i=1,a;i<=n;++i)scanf("%u",&a),tree.set(i,a);
	for(unsigned int opt,x,y;m--;)
	switch(scanf("%u%u%u",&opt,&x,&y),opt){
		case 0:tree.split(x,y),printf("%u\n",tree.query(y));break;
		case 1:if(tree.find(x)!=tree.find(y))tree.link(x,y);break;
		case 2:if(tree.find(x)==tree.find(y))tree.cut(x,y);break;
		case 3:tree.modify(x,y);break;
	}
	return 0;
}