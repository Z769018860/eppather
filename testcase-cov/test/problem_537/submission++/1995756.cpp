#include<bits/stdc++.h>
using namespace std;
string s;
int k, n; 
int num, sum;
int ss[5000006];
int cs[1500005];
int main() {
	cin >> s;
	scanf("%d", &k);
    n = s.size();
    sum = 1;
    for (int i = 1; i < k; ++ i) {
        sum *= 4;
	} 
    for (int i = 0; i  < n; ++ i) {
    	if (s[i] == 'A') {
    		ss[i] = 0;
		}
		if (s[i] == 'G') {
			ss[i] = 1;
		}
		if (s[i] == 'C') {
			ss[i] = 2;
		}
		if (s[i] == 'T') {
			ss[i] = 3;
		}
	}
	num += ss[0];
	for (int i = 1; i < k; ++ i) {
		num *= 4;
		num += ss[i]; 
	}
	cs[num] ++;
	for (int i = 1; i < n; ++ i) {
		if (i + k - 1 >= n) {
			break;
		}
		num -= (ss[i - 1] * sum);
		num *= 4;
		num += ss[i + k - 1];;
		cs[num] ++;
	}
	int maxn = 0;
	for (int i = 0; i <= 1500005; ++ i) {
		maxn = max(maxn, cs[i]);
	}
	printf("%d\n", maxn);
	return 0;
} 