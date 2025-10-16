#include <stdio.h>

int main(void){long long x,y;scanf("%lld",&x);for(int i=1;i<3000000;i++){scanf("%lld",&y);x^=y;}printf("%lld",x);return 0;}