#include<stdio.h>
const int N=1e6+9;
long long tree[N];
int n,m;
long long lbit(int x) {
    return x&(-x);
}
void add(int i,int x) {
    while(i<=n) {
        tree[i]+=x;
        i+=lbit(i);
    }
}
long long cha(int i) {
    long long c=0;
    while(i) {
        c+=tree[i];
        i-=lbit(i);
    }
    return c;
}
void p(void){
for(int i=1; i<=n; i++) {
printf("%lld ",tree[i]);

}
printf("\n");
}
int main()
{
    scanf("%d %d",&n,&m);
    long long l=0;
    for(int i=1; i<=n; i++) {
        int a;
        scanf("%d",&a);
        add(i,a-l);
        l=a;
    }
  
    for(int i=1; i<=m; i++) {
        int a;
        scanf("%d",&a);
        if(a==1) {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);           
            add(l,x);
          
            add(r+1,-x);
        
        }
        else {
            int b;
            scanf("%d",&b);
            printf("%lld\n",cha(b));
        }


    }
    return 0;
}