#include <iostream>
#include <algorithm>
using namespace std;

const int N=(1<<12)+5;
typedef long long ll;
int n,m;
ll t[N][N];
inline int lb(int x){ return x&-x; }
void upd(int x,int y,int k){ for(;x<=n;x+=lb(x)) for(int i=y;i<=m;i+=lb(i)) t[x][i]+=k; }
ll query(int x,int y){ ll ret=0; for(;x;x-=lb(x)) for(int i=y;i;i-=lb(i)) ret+=t[x][i]; return ret; }
int main(){
	scanf("%d%d",&n,&m);
	int op,x,y,u,v;
	while(~scanf("%d%d%d%d",&op,&x,&y,&u)){
		if(op==1) upd(x,y,u);
		else{
			scanf("%d",&v);
			printf("%lld\n",query(u,v)-query(u,y-1)-query(x-1,v)+query(x-1,y-1));
		}
	}
	
	return 0;
}