#include <cstring>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#define ll long long
#define ull unsigned long long
using namespace std;
const ll len=1e7,mod=998244352,N=-0x3fffffff;

ll x,n,a[len],r;

void fp(ll nn)
{
	r=1;
	ll sum=x;
	while(nn)
	{
		if(nn&1){
			r=(r*sum)%mod;
		}
		sum=(sum*sum)%mod;
		nn>>=1;
	}
}

int main()
{
	scanf("%lld %lld",&x,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		fp(a[i]);
		printf("%lld",r);
		if(i!=n){
			printf(" ");
		}
	}
	return 0;
}