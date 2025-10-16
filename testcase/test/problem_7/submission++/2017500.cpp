#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace IO{
	const int SZ=1<<21;
	char buf[SZ],*S,*T,c;int f;
	#define gc() (S==T?(T=(S=buf)+fread(buf,1,SZ,stdin),(S==T?EOF:*S++)):*S++)
	template<class I>
	void read(I&x) {


		scanf("%lld",&x);
	}
}
using IO::read;
int n=3e6;
int main() {
	ll res=0,x;
	while(n--)read(x),res^=x;
	cout<<res<<'\n';
	return 0; 
}