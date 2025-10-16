int n,k,z,i,r,a,b;const int P=1e9+7;
f(){for(r=1;b;b>>=1,a=1ll*a*a%P)if(b&1)r=1ll*r*a%P;return r;}
main(){for(scanf("%d%d",&n,&k),i=1;i<=n;++i)b=k,z=(z+1ll*n/(a=i)*f()%P)%P;printf("%d",z);}