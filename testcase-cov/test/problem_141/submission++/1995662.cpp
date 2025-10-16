#include<bits/stdc++.h>
using namespace std;
const int N = 6e5 + 10, M = 3e5 + 10;
int s[N];
int len[N], tr[N][27], fail[N], cnt[N], dep[N];
int rlst, nT = 1, llst;
void init()
{
	len[1] = -1;
	fail[0] = fail[1] = 1;
}
int L, R;
long long ans = 0;
int find_L(int x)
{
	while(s[L] != s[L + len[x] + 1]) x = fail[x];
	return x;
}
int find_R(int x)
{
	while(s[R] != s[R - len[x] - 1]) x = fail[x];
	return x;
}
char str[N];
void add_L(int ch)
{
	L--;
	s[L] = ch;
	int cur = find_L(llst);
	if(!tr[cur][ch])
	{
		nT++;
		fail[nT] = tr[find_L(fail[cur])][ch];
		tr[cur][ch] = nT;
		len[nT] = len[cur] + 2;
		dep[nT] = dep[fail[nT]] + 1;
	}
	llst = tr[cur][ch];
	if(len[llst] == R - L + 1)
		rlst = llst;
	ans += dep[llst];
}
void add_R(int ch)
{
	R++;
	s[R] = ch;
	int cur = find_R(rlst);
	if(!tr[cur][ch])
	{
		nT++;
		fail[nT] = tr[find_R(fail[cur])][ch];
		tr[cur][ch] = nT;
		len[nT] = len[cur] + 2;
		dep[nT] = dep[fail[nT]] + 1;
	}
	rlst = tr[cur][ch];
	if(len[rlst] == R - L + 1)
		llst = rlst;
	ans += dep[rlst];
}
int main()
{
	init();
	L = M;
	R = L - 1;
	scanf("%s", str);
	int LEN = strlen(str);
	for(int i = 0; i < LEN; i++)
		add_R(str[i] - 'a' + 1);
	int Q;
	scanf("%d", &Q);
	while(Q--)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			scanf("%s", str);
			LEN = strlen(str);
			for(int i = 0; i < LEN; i++)
				add_R(str[i] - 'a' + 1);
		}
		else if(op == 2)
		{
			scanf("%s", str);
			LEN = strlen(str);
			for(int i = 0; i < LEN; i++)
				add_L(str[i] - 'a' + 1);
		}
		else
			printf("%lld\n", ans);
	}
	return 0;
}