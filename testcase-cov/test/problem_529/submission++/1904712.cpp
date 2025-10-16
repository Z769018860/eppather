#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=1e6+5;
ll T,n,a,b;
char s[_];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>(s+1);n=strlen(s+1);a=b=(n>1||s[1]!='V');
		for(ll i=1;i<n;i++)
			if(s[i]=='N'&&s[i+1]=='N')a=b=0;
		if(s[1]=='V')b=0;
		cout<<a<<' '<<b<<'\n';
	}
	return 0;
}