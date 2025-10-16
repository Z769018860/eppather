#include<stdio.h>
#include<cctype>
#include<algorithm>
int read(){
    char ch;
    while(!isdigit(ch=getchar()));
    int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int _inf=-2e9,N=100,M=101;
std::pair<int,int> t[N];
int n,m;
int f[2][M];
inline bool check(int &k){
    f[0][0]=0;std::fill(&f[0][1],&f[0][m+1],_inf);
    f[1][0]=0;std::fill(&f[1][1],&f[1][m+1],_inf);
    for(int i=0;i<n;i++){
        for(int j=0;j<=m&&j<=k/t[i].first;j++) {
            const int tmp=(k-j*t[i].first)/t[i].second;
            for(int l=m-j;l>=0;l--) {
                f[i&1][j+l]=std::max(f[i&1][j+l],f[!(i&1)][l]+tmp);
            }
        }
    }
    return f[!(n&1)][m]>=m;
}
int main(){
    n=read();m=read();
    for(int i=0;i<n;i++) t[i]={read(),read()};
    int l=0,r=1e8;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
		else l=mid+1;
    }
    printf("%d\n",(l+r)>>1);
    return 0;
}