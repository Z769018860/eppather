#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace IO{
	const int SZ=1<<21;
	char buf[SZ],*S,*T,c;int f;
	#define gc() (S==T?(T=(S=buf)+fread(buf,1,SZ,stdin),(S==T?EOF:*S++)):*S++)
	template<class I>
	void read(I&x) {
		cin>>x;
	}
}
using IO::read;
int n=3e6;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll res=0,x;
	while(n--)read(x),res^=x;
	cout<<res<<'\n';
	return 0; 
}