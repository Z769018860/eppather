#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+1;
struct SAM{
    int fa,len;
    map<char,int> son;
}nd[maxn<<1];
vector<int> E[maxn<<1];
int lst,tot;
int ans[maxn],rk;
int dp[maxn<<1];
void ins(char c){
    if(nd[lst].son[c]!=0){
        int q=nd[lst].son[c],v=lst;
        if(nd[q].len==nd[v].len+1){
            lst=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[q].fa=nd[v].fa=nq;
            lst=nq;
            while(v!=0&&nd[v].son[c]==q) nd[v].son[c]=nq,v=nd[v].fa;
            return ;
        }
    }
    int u=++tot,v=lst;
    lst=u;
    nd[u].len=nd[v].len+1;
    while(v!=0&&nd[v].son[c]==0) nd[v].son[c]=u,v=nd[v].fa;
    if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c];
        if(nd[q].len==nd[v].len+1){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[q].fa=nd[u].fa=nq;
            while(v!=0&&nd[v].son[c]==q) nd[v].son[c]=nq,v=nd[v].fa;
            return ;
        }
    }
}
void init(){
    for(int i=1;i<=tot;i++) nd[i].son.clear();
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
}
void dfs(int u){
    for(int v:E[u]){
        dfs(v);
        if(dp[u]==0&&dp[v]!=0) dp[u]=-abs(dp[v]);
    }
}
string t;
bool cmp(int x,int y){
    return t[abs(dp[x])-nd[nd[x].fa].len-1]<t[abs(dp[y])-nd[nd[y].fa].len-1];
}
void solve(int u){
    if(dp[u]>0) ans[++rk]=dp[u];
    sort(E[u].begin(),E[u].end(),cmp);
    for(int v:E[u]){
        solve(v);
    }
}
int main(){
    lst=++tot;
    string s;
    cin>>s;
    int len=s.size();
    for(int i=len-1;i>=0;i--) t+=s[i];
    for(int i=0;i<len;i++){
        ins(t[i]);
        dp[lst]=i+1;
    }
    init();
    dfs(1);
    solve(1);
    for(int i=1;i<=len;i++) cout<<len-ans[i]+1<<' ';
    return 0;
}