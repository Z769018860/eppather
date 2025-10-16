#include<cstdio>

int k;

int euler(int n) {
    int ans=n;
    for (int i=2;i*i<=n;i++){
        if (!(n%i)) {
            ans=ans/i*(i-1);
            while(!(n%i)) n/=i;
        }
    }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}

int main(){
    scanf("%d",&k);
    if(k==1){
        printf("-1");
        return 0;
    }
    int phi=euler(k);
    int n=phi<<1;
    printf("%d\n",n);
    for(int i=0;i<n;i++){
        printf("%d ",i==phi? k-1:0);
    }
    printf("1");
    return 0;
}