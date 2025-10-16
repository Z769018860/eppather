#include<bits/stdc++.h>
using namespace std;

long long read(){
	long long a = 0; char c = getchar(); while(!isdigit(c)) c = getchar();
	while(isdigit(c)){a = a * 10 + c - 48; c = getchar();} return a;
}

map < long long , int > dp; int T;

int main(){
	dp[1] = 0;
	for(int i = 2 ; i <= 5 ; ++i){
		auto p = dp.begin();
		while(6e18 / i >= p->first){
			long long x = p->first * i;
			if(dp.find(x) == dp.end()) dp[x] = p->second + i + 1;
			else dp[x] = min(dp[x] , p->second + i + 1);
			++p;
		}
	}
	int pre = 1e9; for(auto t = dp.rbegin() ; t != dp.rend() ; ++t) pre = t->second = min(t->second , pre);
	dp[1] = 2; for(T = read() ; T ; --T){long long Q = read(); printf("%d\n" , 2 * dp.lower_bound(Q)->second);}
	return 0;
}