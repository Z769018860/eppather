#include<bits/stdc++.h>

#define int long long

using namespace std;

char s[5000005];
int a[5000005];
int n;
int k;
int sab[15];
map<int,int> mp;
int ans[5000005];
int cn;
int x;

int po(int x){
	int res = 1;
	while(x--) res *= 10;
	return res;
}

signed main(){
	
	cin >> s+1 >> k;
	n = strlen(s+1);
	for(int i = 1;i <= n;++ i){
		if(s[i] == 'A') a[i] = 1;
		if(s[i] == 'C') a[i] = 2;
		if(s[i] == 'G') a[i] = 3;
		if(s[i] == 'T') a[i] = 4;
	}
	
	int t = 0;
	x = po(k);
	for(int i = 1;i < k;++ i)
		t = t*10+a[i];
	for(int i = k;i <= n;++ i){
		int j = i-k+1;
		t = t*10+a[i];
		t = t%x;
		mp[t]++;
		if(mp[t] == 1) ans[++cn] = t;
	}
	
	int da = 0;
	for(int i = 1;i <= cn;++ i)
		da = max(da,mp[ans[i]]);
	
	cout << da;
	
	return 0;
	
} 