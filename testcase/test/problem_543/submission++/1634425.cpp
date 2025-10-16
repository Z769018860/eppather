#include<bits/stdc++.h>
using namespace std;

int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

int main(){
	int T=read();while(T--){
		int n=read(),k=read();
		for(int i=1;i<=k;i++){
			int x=read(),y=read(),z=read();
		}long long ans=n*n-k;
		if(ans&1ll)printf("YES\n");
		else printf("NO\n");
	}
	
}