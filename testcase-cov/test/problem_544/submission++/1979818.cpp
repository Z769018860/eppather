#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,ans[N];
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	
	n=read();
	cout<<n+1<<"\n";
	int now=n+1;
	for (int i=n+1;i>=1;i-=2) ans[i]=now--;
	for (int i=((n&1)?1:2);i<=n+1;i+=2) ans[i]=now--;
	for (int i=1;i<=n+1;i++) cout<<ans[i]<<" ";
	puts("");
	return 0;
}
