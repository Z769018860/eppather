using namespace std;
#include<bits/stdc++.h>






#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1005
#define LL long long
#define LD long double
#define int LL

#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();
while(c<'0'||c>'9'){c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n;
int m;
int a[N],b[N];
int dp[N][N];
int check(int mid){

	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)dp[i][j]=-INF;
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++){
				if(j-k>mid/a[i])continue;
				dp[i][j]=Max(dp[i][j],dp[i-1][k]+(mid-a[i]*j+a[i]*k)/b[i]);
			}
		}
	}
	return (dp[n][m]>=m);
}
signed main(){
	read(n);
	read(m);
	for(int i=1;i<=n;i++)read(a[i]),read(b[i]);
	int l=0,r=INF;





	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	write(l);
	return 0;
}
