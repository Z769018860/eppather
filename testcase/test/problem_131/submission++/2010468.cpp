#include<cstdio>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)

typedef long long ll;

const int N=1e6+5;
int a[N],n,q;
ll t[N];

int lowbit(int k){
	return k&-k;
}
void update(int x,int k){
	for(;x<=n;x+=lowbit(x)){
		t[x]+=k;
	}
}
ll query(int x){
	ll r=0;
	for(;x;x-=lowbit(x)){
		r+=t[x];
	}
	return r;
}
int main(){
	int i,o,x,y,k;
	scanf("%d%d",&n,&q);
	UP(i,1,n){
		scanf("%d",&a[i]);
		update(i,a[i]-a[i-1]);
	}
	UP(i,1,q){
		scanf("%d%d",&o,&x);
		if(o==1){
			scanf("%d%d",&y,&k);
			update(x,k);
			update(y+1,-k);
		}else{
			printf("%lld\n",query(x));
		}
	}
	return 0;
}