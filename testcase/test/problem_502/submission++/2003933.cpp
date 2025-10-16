#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define K 2187
#define mod 1000003
#define ll long long
vector<int>mat[mod];
int n,m,x,y,ans,init[K][K];
ll R[N],dep[N<<1];
int read() {
	int x=0,flag=0;
	char c=getchar();
	while ((c<'0')||(c>'9')) {
		if (c=='-')flag=1;
		c=getchar();
	}
	while ((c>='0')&&(c<='9')) {
		x=x*10+c-'0';
		c=getchar();
	}
	if (flag)x=-x;
	return x;
}
void write(int x) {
	if (x<0) {
		putchar('-');
		x=-x;
	}
	int num[11];
	num[0]=0;
	while (x) {
		num[++num[0]]=x%10;
		x/=10;
	}
	if (!num[0])putchar('0');
	for(int i=num[0]; i; i--)putchar(num[i]+'0');
	putchar('\n');
}
int add_low(int x,int y) {
	int s=1,ans=0;
	for(int i=0; i<7; i++) {
		ans=ans+(x+y)%3*s;
		s*=3,x/=3,y/=3;
	}
	return ans;
}
ll add_high(ll x,ll y) {
	ll s=1,ans=0;
	for(int i=0; i<5; i++) {
		ans=ans+init[x%K][y%K]*s;
		s*=K,x/=K,y/=K;
	}
	return ans;
}
int main() {
	srand(time(0));
	for(int i=0; i<K; i++)
		for(int j=0; j<K; j++)init[i][j]=add_low(i,j);
	n=read(),m=read();
	for(int i=1; i<=n; i++) {
		for(int j=0; j<35; j++)R[i]=R[i]*3+rand()%3;
		mat[R[i]%mod].push_back(i);
		mat[add_high(R[i],R[i])%mod].push_back(i);
	}
	for(int i=1; i<=m; i++) {
		x=read(),y=read();
		x^=ans,y^=ans;
		dep[i]=add_high(dep[y],R[x]);
		if (!dep[i])ans=-1;
		else {
			ans=-2;
			for(int j=0; j<mat[dep[i]%mod].size(); j++) {
				ll x=R[mat[dep[i]%mod][j]];
				if ((x==dep[i])||(add_high(x,x)==dep[i])) {
					ans=mat[dep[i]%mod][j];
					break;
				}
			}
		}
		write(ans);
	}
	return 0;
}