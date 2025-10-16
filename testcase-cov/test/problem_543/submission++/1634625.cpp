#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T&x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	x*=f;
}
int t,n,k,tmp;
int main(){
	read(t);
	while(t--){
		read(n);read(k);
		for(int i=0;i<k;++i)read(tmp),read(tmp),read(tmp);
		puts((n^k)&1?"YES":"NO");
	}
}
