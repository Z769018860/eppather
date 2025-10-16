#include<bits/stdc++.h>
#define ll long long
#define re register
#define cs const
#define int ll

using std::cerr;
using std::cout;

int calc(int p,int t,int pw){
	int q=1;
	for(int re i=1;i<=t;++i)q*=p;
	q=q/p*(p-1);if(p==2&&t>2&&pw%2==0)q/=2;
	return q/std::__gcd(q,pw);
}

int solve(int p,int t,int pw){
	int res=1;
	while(t>0){
		res+=calc(p,t,pw);
		t-=pw;
	}return res;
}

int tim,_,n;

void Main(){
	std::cin>>tim>>_>>n;int res=1;
	for(int re i=2;(ll)i*i<=n;++i)
		if(n%i==0){
			int t=0;while(n%i==0)n/=i,++t;
			res*=solve(i,t,tim);
		}
	if(n>1)res*=solve(n,1,tim); 
	cout<<res<<"\n";
}

inline void file(){
#ifdef zxyoi
	freopen("homework.in","r",stdin);
#endif
}signed main(){file();Main();return 0;} 