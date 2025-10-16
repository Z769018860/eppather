#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
const int NR=2e6+10;
vector<int>to[NR];
int n,d,match0[NR],match1[NR],vis[NR],p[NR],st[NR],top;
mt19937 rnd(time(0));

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		to[i].resize(d);
		for(int j=0;j<d;j++)cin>>to[i][j];
	}
	for(int i=1;i<=n;i++)p[i]=i;
	shuffle(p+1,p+1+n,rnd);
	for(int i=1;i<=n;i++){
		int now=p[i],nxt;
		vis[now]=i;st[top=1]=now;
		while(1){
			nxt=to[now][rnd()%d];
			while(nxt==match0[now])nxt=to[now][rnd()%d];
			if(!match1[nxt])break;
			now=match1[nxt];
			while(vis[now]==i)vis[st[top--]]--;
			st[++top]=now;vis[now]=i;
		}
		for(int i=1;i<top;i++){
			match0[st[i]]=match0[st[i+1]];
			match1[match0[st[i+1]]]=st[i];
		}
		match0[now]=nxt;match1[nxt]=now;
	}
	for(int i=1;i<=n;i++)cout<<match0[i]<<' ';
	return 0;
}