
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> PII;
template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch;
	while((ch = getchar()) > '9' || ch < '0') if(ch == '-') f = -1;
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ '0'),ch = getchar();
	x *= f;
}

const int N = 1e5 + 5;

int k,a[N];

int main()
{
	int k; read(k);
	int l = 1,r = k + 1;
	for(int i = 1;i <= k + 1;i++)
		if(i & 1) a[i] = r--;
		else a[i] = l++;
	printf("%d\n",k + 1);
	for(int i = k + 1;i;i--) printf("%d%c",a[i]," \n"[i == 1]);
	return (0-0); 
}