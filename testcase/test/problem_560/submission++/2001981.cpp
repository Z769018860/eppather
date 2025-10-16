#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <assert.h>
#include <bitset>
#include <time.h>
#include <math.h>
#include <deque>
#include <set>
#define in(x) freopen(#x".in","r",stdin)
#define out(x) freopen(#x".out","w",stdout)
#define make(x) freopen(#x".in","w",stdout)
#define ll long long
#define int long long
#ifdef MY_COMPUTER
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) void(0)
#endif

using namespace std;

inline int read()
{
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
int n,k,t[1000010],ans[1000010],ct,to[1000010],h,lst,lmt;
char s[1000010];
signed main()
{
	
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=n;i;i--)
		if(s[i]=='*'){
			if(ct&1){
				t[h]=1;
				if(ct==1)
					to[h]=lst;
			}
			ct>>=1,to[++h]=-1;
		}
		else if(!ct++) lst=h;
	while(ct){
		if(ct&1){
			t[h]=1;
			if(ct==1)
				to[h]=lst;
		}
		ct>>=1,to[++h]=-1;
	}
	lmt=k-1;
	for(int i=h;~i&&~lmt;i--)
		if(t[i])
			if(i>lmt)
			{
				int ok=0;
				if(~to[i])
					for(int j=to[i];j<i;++j)
						if(!t[j])
							t[j]=ok=1;
				if(!ok) ans[lmt--]=1;
			}
			else ans[i]=1;
	int t=k-1;
	while(t&&!ans[t]) --t;
	for(int i=t; ~i; --i) putchar('0'+ans[i]);
	return 0;
}
