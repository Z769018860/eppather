#include<cstdio>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)

typedef long long ll;

const int N=3e6+5;
int n,p;
ll inv[N];

int main(){
	int i;
	inv[1]=1;
	scanf("%d%d",&n,&p);
	printf("1\n");
	UP(i,2,n){
		inv[i]=(p-p/i)*inv[p%i]%p;
		printf("%lld\n",inv[i]);
	}
	return 0;
}