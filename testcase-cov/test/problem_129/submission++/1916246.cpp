#include <bits/stdc++.h>
using namespace std;
#define IO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

vector<string> duval(string const& s) {
	int n = s.size(), i = 0;
	vector<string> factorization;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				k++;
			j++;
		}
		while (i <= k) {
			factorization.push_back(s.substr(i, j - k));
			i += j - k;
		}
	}
	return factorization;
}

vector<int> duval2(string const& s) {
	int n = s.size(), i = 0;
	vector<int> factorization;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j])
				k = i;
			else
				k++;
			j++;
		}
		while (i <= k) {
			i += j - k;
			factorization.push_back(i);
			
		}
	}
	return factorization;
}
int main()
{
	IO;
	string s;
	cin>>s;
	auto v=duval2(s);
	for(auto i:v)
	{
		cout<<i<<" ";
	}
	return 0;
}