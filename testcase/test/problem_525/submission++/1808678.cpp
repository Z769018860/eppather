#include <cstdio>
int k;
int gcd(int x,int y){
    if(!y) return x;
    return gcd(y,x%y);
}
int main(){
    scanf("%d",&k);
    if(k==1){puts("-1");return 0;}
    int phi=1;
    for(int i=2;i<k;i++) if(gcd(i,k)==1) phi++;
    printf("%d\n",phi<<1);
    for(int i=0;i<phi;i++) printf("0 ");
    printf("%d ",k-1);
    for(int i=phi+1;i<(phi<<1);i++) printf("0 ");
    printf("1");
    return 0;
}