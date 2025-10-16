#include<bits/stdc++.h>
#define pt putchar(' ')
#define nl puts("")
#define pb push_back
#define pi pair<int,int>
#define go(it) for(auto &it:as[x])
using namespace std;

const int N=1e6+10;
int n,m,idx,lt;
int E[N][26],fa[N],R[N],rk[N],ct[N],f[N],ans[N];
char s[N];

int fr(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*flag;
}
void fw(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) fw(x/10);
	putchar(x%10+'0');
}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}

void ins(int c)
{
	int p=lt,now=lt=++idx;
	R[now]=R[p]+1;
	while(~p && !E[p][c]) E[p][c]=now,p=fa[p];
	if(!~p) return void(fa[now]=0);
	
	int q=E[p][c];
	if(R[q]==R[p]+1) return void(fa[now]=q);
	int cy=++idx;
	R[cy]=R[p]+1,fa[cy]=fa[q];
	memcpy(E[cy],E[q],sizeof E[cy]);
	while(~p && E[p][c]==q) E[p][c]=cy,p=fa[p];
	fa[now]=fa[q]=cy;
}

void Radix_sort()
{
	for(int i=1;i<=idx;i++) ct[R[i]]++;
	for(int i=1;i<=n;i++) ct[i]+=ct[i-1];
	for(int i=idx;i;i--) rk[ct[R[i]]--]=i;
}

int main()
{
	m=fr()-1;
	scanf("%s",s+1);
	n=strlen(s+1),fa[0]=-1;
	for(int i=1;i<=n;i++) ins(s[i]-'a');
	Radix_sort();
	
	memset(ans,0x3f,sizeof ans);
	while(m--)
	{
		memset(f,0,(idx+1)*sizeof f[0]);
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1,now=0,len=0;i<=n;i++)
		{
			int c=s[i]-'a';
			while(~now && !E[now][c]) now=fa[now],len=R[now];
			if(!~now) len=0,now=0;
			if(E[now][c]) now=E[now][c],len++;
			f[now]=max(f[now],len);
		}
		
		for(int i=idx;i;i--)
		{
			f[fa[rk[i]]]=max(f[fa[rk[i]]],min(R[fa[rk[i]]],f[rk[i]]));
			ans[rk[i]]=min(ans[rk[i]],f[rk[i]]);
		}
	}
	
	int res=0;
	for(int i=1;i<=idx;i++) res=max(res,ans[i]);
	fw(res);
}