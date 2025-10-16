#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,flag;
char s[100];
int a[N],tree[N],b[N];
int get(int x){
	int ans=0;
	while (x){
		ans+=tree[x];
		x-=(x&(-x));
	}
	return ans;
}
void put(int x){
	while (x<=n){
		tree[x]++;
		x+=(x&(-x));
	}
}
int main(){
	scanf("%d",&n);
	int op=0;
	for (int i=1;i<=n;i++){
		scanf("%s",s);
		if (s[0]=='X') op^=1,flag=1;
		else{
			int pos=0,f=1;
			if (s[0]=='-') pos=1,f=-1; else pos=0;
			for (int j=pos;j<strlen(s);j++) a[i]=a[i]*10+(s[j]-'0');
			a[i]*=f;
		}
	}
	if (flag){
		if (op&&n!=1) puts("W"); else puts("L");
	}else{
		vector<int>s;
		for (int i=1;i<=n;i++) s.push_back(a[i]);
		sort(s.begin(),s.end());
		for (int i=1;i<=n;i++) a[i]=lower_bound(s.begin(),s.end(),a[i])-s.begin()+1;
		for (int i=n;i>=1;i--){
			op^=(get(a[i])&1);
			put(a[i]);
		}
		if (op) puts("W"); else puts("L");
	}
}