n,k,z,i,r,a,b;const P=1e9+7;
main(){for(scanf("%d%d",&n,&k),i=1;b=k,(a=i)<=n;z=(z+1ll*n/i*r%P)%P,++i)for(r=1;b;b/=2,a=1ll*a*a%P)if(b&1)r=1ll*r*a%P;printf("%d",z);}