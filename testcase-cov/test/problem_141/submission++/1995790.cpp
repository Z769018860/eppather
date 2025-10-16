#include<bits/stdc++.h>
using namespace std;
const int N=800005;
char S[N];
int l,r,len[N],fail[N],ch[N][27],tot=1,last[2],dep[N],s[N];
long long ans;
inline int getpos(int p,int op){
	if(op){
		while(s[l]!=s[l+1+len[p]])p=fail[p];
	}
	else{
		while(s[r]!=s[r-1-len[p]])p=fail[p];
	}
	return p;
}
inline void insert(int x,int op){
	if(op)s[--l]=x;
	else s[++r]=x;
	int p=getpos(last[op],op);
	if(!ch[p][x])len[++tot]=len[p]+2,fail[tot]=ch[getpos(fail[p],op)][x],dep[tot]=dep[fail[tot]]+1,ch[p][x]=tot;
	last[op]=ch[p][x];
	if(len[last[op]]==r-l+1)last[!op]=last[op];
	ans+=dep[last[op]];
}
int main(){
	l=400000;
	r=l-1;
	len[1]=-1;
	fail[0]=1;
	scanf("%s",S+1);
	int len=strlen(S+1),Q;
	scanf("%d",&Q);
	for(int i=1;i<=len;++i)insert(S[i]-'a'+1,0);
	int op;
	while(Q--){
		scanf("%d",&op);
		if(op<=2){
			scanf("%s",S+1);
			len=strlen(S+1);
			for(int i=1;i<=len;++i)insert(S[i]-'a'+1,op-1);
		}
		else printf("%lld\n",ans);
	}
}