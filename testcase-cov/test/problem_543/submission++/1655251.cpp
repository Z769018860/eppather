#include<bits/stdc++.h>
using namespace std;
int main(){ int T,n,k,x,y,z; scanf("%d",&T); while(T--){ scanf("%d%d",&n,&k); for(int i=1;i<=k;i++) scanf("%d%d%d",&x,&y,&z); puts(((n*n-k)%2==0)?"NO":"YES"); } }