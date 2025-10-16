#include<cstdio>
bool ava[30010];
int k;
void del(int x){
	if(x==1)return;
	for(int i=x;i<=k;i+=x)ava[i]=1;
}
int main(){
	int fhi=0,i;
	scanf("%d",&k);
	if(k==1){printf("-1\n");return 0;}
	for(i=1;i*i<k;i++)
		if(k%i==0){del(i);del(k/i);}
	if(i*i==k)del(i);
	for(int i=1;i<=k;i++)if(!ava[i])fhi++;
	printf("%d\n",fhi*2);
	for(i=0;i<fhi;i++)printf("0 ");printf("%d ",k-1);
	for(i=1;i<fhi;i++)printf("0 ");printf("1\n");
}