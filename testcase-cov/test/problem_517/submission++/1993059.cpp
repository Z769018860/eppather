#include<bits/stdc++.h>
#define MAXN 220500
#define MAXW 32
using namespace std;
namespace wzk{
	int n,yn;
	int a[MAXN<<1];
	struct node{
		int son[2];
		int bj;
	}trie[MAXN<<5];
	int tot=1;
	int s[MAXN<<5][MAXW+2];
	void insert(int x){
		int u=1;
		for(int i=MAXW-1;i>=0;i--){
			trie[u].bj++;
			int w=(x>>i)&1;
			for(int i=MAXW-1;i>=0;i--) s[u][i]+=(x>>i)&1;
			if(trie[u].son[w]) u=trie[u].son[w];
			else{
				trie[u].son[w]=++tot;
				u=tot;
			}
		}
		trie[u].bj++;
		for(int i=MAXW-1;i>=0;i--) s[u][i]+=(x>>i)&1;
	}
	int op,l,r,x;
	int allxor,last;
	long long sum[MAXN][MAXW+2];
	long long yquery(int k){
		if(!k) return 0;
		int u=1,ww=0;
		long long ret=0;
		for(int i=MAXW-1;i>=0;i--){
			int w=(last>>i)&1;
			if(k<=trie[trie[u].son[w]].bj) u=trie[u].son[w],ww|=w<<i;
			else{
				k-=trie[trie[u].son[w]].bj;
				for(int j=MAXW-1;j>=0;j--){
					int cnt=s[trie[u].son[w]][j];
					if((allxor>>j)&1) cnt=trie[trie[u].son[w]].bj-cnt;
					ret+=(1ll*cnt)<<j;
				}
				u=trie[u].son[w^1];
				ww|=(w^1)<<i;
			}
		}
		return ret+1ll*k*(ww^allxor);
	}
	long long wquery(int l,int r){
		long long ret=0;
		for(int i=MAXW-1;i>=0;i--){
			int cnt=sum[r][i]-sum[l-1][i];
			if((allxor>>i)&1) cnt=r-l+1-cnt;
			ret+=(1ll*cnt)<<i;
		}
		return ret;
	}
	long long query(int l,int r){
		if(r<=yn) return yquery(r)-yquery(l-1);
		if(l>yn) return wquery(l,r);
		return yquery(yn)-yquery(l-1)+wquery(yn+1,r);
	}
	int m;
	int main(){
		
		
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			for(int j=MAXW-1;j>=0;j--){
				sum[i][j]=sum[i-1][j]+((a[i]>>j)&1);
			}
		}
		scanf("%d",&m);
		while(m--){
			scanf("%d",&op);
			if(op==1){
				scanf("%d",&x);
				x^=allxor;
				a[++n]=x;
				for(int i=MAXW-1;i>=0;i--){
					sum[n][i]=sum[n-1][i]+((x>>i)&1);
				}
			}else if(op==2){
				scanf("%d%d",&l,&r);
				printf("%lld\n",query(l,r));
			}else if(op==3){
				scanf("%d",&x);
				allxor^=x;
			}else{
				for(int i=yn+1;i<=n;i++) insert(a[i]);
				last=allxor,yn=n;
				for(int j=0;j<=MAXW+1;j++){
					sum[n][j]=0;
				}
			}
		}
		return 0;
	}
}
signed main(){
	return wzk::main();
}