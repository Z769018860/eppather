#include<bits/stdc++.h>
using namespace std;
string a;
int k;
unordered_map<string,int>ap;
int main(){
	cin >> a >> k;
	for(int i=0;i<a.length();i++)
	{
		ap[a.substr(i,k)]++;
	}
	int ans = 0;
	for(auto v:ap)
		ans = max(ans,v.second);
	cout << ans;
	return 0;
}