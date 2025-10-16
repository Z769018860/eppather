#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define int ll
const int MAXN = 2e6 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int _ = 0;
const bool debug = false;
int T;
signed main()
{
	
    cin >> T;
	while(T--)
	{
		string s;
		cin >> s;
		if(s.size() == 1)
		{
			if(s == "N")cout << "1 1" << endl;
			else cout << "0 0" << endl;
			continue;
		}
		bool flag = false;
		for(int i = 0; i < s.size() - 1; i++)
		{
			if(s[i] == s[i + 1] && s[i] == 'N')
			{
				flag = true;
			}
		}
		if(flag)
		{
			cout << "0 0" << endl;
		}
		else
		{
			if(s[0] == 'N')cout << "1 1" << endl;
			else cout << "1 0" << endl;
		}
	}
	
    return ~~(0^_^0);
}