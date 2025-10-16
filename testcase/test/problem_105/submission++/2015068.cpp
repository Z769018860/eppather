#include<bits/stdc++.h>
using namespace std;
const int MAXN  = 1e6;
int n,m,minn,anss;

int root,tot;
struct BST_Splay{
	int data;
	int fath;
	int lson;
	int rson;
	int sum;
	int k;
	bool lazy;
}tree[MAXN];
void pushup(int x){
	tree[x].sum = tree[tree[x].lson].sum+tree[tree[x].rson].sum+tree[x].k;
}
void pushdown(int x){
	if(tree[x].lazy){
		tree[tree[x].lson].lazy^=1;
		tree[tree[x].rson].lazy^=1;
		swap(tree[tree[x].lson].lson,tree[tree[x].lson].rson);
		swap(tree[tree[x].rson].lson,tree[tree[x].rson].rson);
		tree[x].lazy^=1;
	}
}
void zig(int x){
	int y = tree[x].fath;
	int z = tree[y].fath;
	int B = tree[x].rson;
	tree[x].rson = y;
	tree[y].fath = x;
	tree[y].lson = B;
	if(B) tree[B].fath = y;
	tree[x].fath = z;
	if(z){
		if(y==tree[z].lson) tree[z].lson = x;
		else tree[z].rson = x;
	}else root = x;
	pushup(y);
	pushup(x);
}
void zag(int x){
	int y = tree[x].fath;
	int z = tree[y].fath;
	int B = tree[x].lson;
	tree[x].lson = y;
	tree[y].fath = x;
	tree[y].rson = B;
	if(B) tree[B].fath = y;
	tree[x].fath = z;
	if(z){
		if(y==tree[z].lson) tree[z].lson = x;
		else tree[z].rson = x;
	}else root = x;
	pushup(y);
	pushup(x);
}
void splay(int x,int to){
	pushdown(x);
	auto fa = tree[x].fath;
	if(fa==to||x==to) return;
	while(fa!=to){
		auto p = tree[fa].fath;
		if(p==to){
			if(tree[fa].lson == x){
				zig(x);
			}else{
				zag(x);
			}
		}else{
			if(tree[fa].lson == x){
				if(tree[p].lson == fa){
					zig(fa);
					zig(x);
				}else{
					zig(x);
					zag(x);
				}
			}else{
				if(tree[p].lson == fa){
					zag(x);
					zig(x);
				}else{
					zag(fa);
					zag(x);
				}
			}
		}
		fa = tree[x].fath;
	}
}
void insert(int x){
	if(!root){
		root = ++tot;
		tree[tot].data = x;
		tree[tot].sum++;
		tree[tot].k++;
		return;
	}
	auto now = root;
	bool lr = false;
	++tot;
	while(true){
		if(x < tree[now].data){
			if(tree[now].lson){
				now = tree[now].lson;
			}else{
				lr = 1;
				break;
			}
		}else if(x==tree[now].data){
			tree[now].k++;
			splay(now,0);			
			return;
		}else{
			if(tree[now].rson){
				now = tree[now].rson;
			}else{
				lr = 0;
				break;
			}
		}
	}
	if(lr){
		tree[now].lson = tot;
		tree[tot].fath = now;
		tree[tot].data = x;
	}else{
		tree[now].rson = tot;
		tree[tot].fath = now;
		tree[tot].data = x;
	}
	tree[tot].sum++;
	tree[tot].k++;
	splay(tot,0);
}
int find_kth(int k){
	int now = root;
	while(now){
		pushdown(now);
		if(k-1==tree[tree[now].lson].sum){
			return now;
		}
		if(k>tree[tree[now].lson].sum){
			k -= 1;
			k -= tree[tree[now].lson].sum;
			now = tree[now].rson;
		}else{
			now = tree[now].lson;
		}
	}
}
void modify(int l,int r){
	l++;r++;
	int p = find_kth(l-1),q = find_kth(r+1);
	splay(p,0);
	splay(q,p);
	tree[tree[q].lson].lazy^=1;
	swap(tree[tree[q].lson].lson,tree[tree[q].lson].rson);
}
void answer(int k){
	if(!k) return;
	pushdown(k);
	answer(tree[k].lson);
	if(!(tree[k].data==0||tree[k].data==n+1))printf("%d ",tree[k].data);
	answer(tree[k].rson);
}
signed main(){
	scanf("%d",&n);
	for(int i = 0;i<=n+1;i++){
		insert(i);
	}
	scanf("%d",&m);
	for(int i = 1;i<=m;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		modify(l,r);
	}
	answer(root);
	return 0;
}