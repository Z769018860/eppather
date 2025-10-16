#include<bits/stdc++.h>
#define int long long

template<typename T>
void read(T &s){
	s=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') s=s*10+(int)(c-'0'),c=getchar();
	s*=f;
	return ;
}

template<typename T>
void aabs(T &s){
	if(s<0) s=-s;
	return ;
}

template<typename T>
void chkmin(T &a,T b){
	a=std::min(a,b);
}

template<typename T>
void chkmax(T &a,T b){
	a=std::max(a,b);
}

const int inf=1e18+2,MOD1=99824453,MOD2=1e9+7;

std::string s;

int k;

const int maxn=1e7;

int t[maxn];

int to(char c){
	if(c=='A') return 1;
	if(c=='G') return 0;
	if(c=='C') return 2;
	return 3;
}

signed main(){
	std::cin>>s;
	read(k);

	for(int i=0;i<s.size();i++) s[i]=to(s[i]);
	int now=0;
	for(int i=0;i<k;i++) now=now*4+s[i];

	t[now]++;
	int ans=0;
	for(int i=k;i<s.size();i++){
		now-=s[i-k]*std::pow(4,k-1);
		now*=4;
		now+=s[i];

		t[now]++;
		chkmax(ans,t[now]);
	}
	printf("%lld",ans);
	
	return 0;
}
