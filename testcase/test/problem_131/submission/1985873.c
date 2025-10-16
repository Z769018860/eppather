#include <stdio.h>
typedef long long ll;
ll t[1000005];
int q,n,b[1000005],a[1000005];

int lowbit(int x){
	return x&(-x);
}

void add(int pos,int k){
	int i;
	for(i=pos;i<=n;i+=lowbit(i))
		t[i]+=k;
	return;
}

ll ask(int pos){
	int i;
	ll ans=0;
	for(i=pos;i;i-=lowbit(i))
		ans+=t[i];
	return ans;
}

int main() {
	int judge,i;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i]-a[i-1];
		add(i,b[i]);
	}
	while(q--){
		scanf("%d",&judge);
		if(judge==1){
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			add(l,x);
			add(r+1,-x);
		}else{
			int x;
			scanf("%d",&x);
			printf("%lld\n",ask(x));
		}
	}
	
	return 0;
}