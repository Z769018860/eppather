#include<stdio.h>
const int N=1e6+9;
long long tree[N];
int n,m;
long long lbit(long long x) {
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
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++) {
        int a;
        scanf("%d",&a);
        add(i,a);
    }

    for(int i=1; i<=m; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(a==1) {
            add(b,c);

        }
        else {
            printf("%lld\n",cha(c)-cha(b-1));
        }


    }
    return 0;
}