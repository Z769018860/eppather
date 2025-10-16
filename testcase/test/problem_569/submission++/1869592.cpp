#include <bits/stdc++.h>
#define f(c,a,b) for(c=a;c<=b;++c)
#define fd(c,a,b) for(c=b;c>=a;--c)
#define ll unsigned long long

#define mp make_pair
#define il inline
#define ri register
#define co const
using namespace std;
const int N=3e5+5;
il int read() {
	ri int ans=0;
	ri char c=getchar();
	ri bool neg=0;
	while((c<'0')|(c>'9')) neg^=!(c^'-'),c=getchar();
	while((c>='0')&(c<='9')) ans=(ans<<3)+(ans<<1)+c-48,c=getchar();
	return neg?-ans:ans;
}

int n,m,k,i,j;

int to[N];

bitset<N>vis;
vector<int>a[N]; 
int ans;
il bool match(const int x){
	for(int it:a[x]){
		if(vis[it]) continue;
		vis[it]=1;
		if(!to[it]||match(to[it])){
			to[it]=x;
			return 1;	
		}
	}
	return false;
} 

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
string s[N];
inline int getnum(const int itt,const int jt) {
    return (itt - 1) * m + jt;
}
signed main() {
	n=read(),m=read();
    f(i,1,n){
        cin>>s[i];
        s[i] = "0" + s[i];
    }
    for(i=1;i<=n;++i){
        for(j=1;j<=m;++j){
            if (s[i][j] == '2') {
                ++ans;
            } else if (s[i][j] == '1') {
                for(k=0;k<=3;++k){
                    if (i + dx[k] <= 0 || n + 1 <= i + dx[k] || j + dy[k] <= 0 || m + 1 <= j + dy[k] ||s[i + dx[k]][j + dy[k]] != '3')
                        continue;
                    a[getnum(i, j)].push_back(getnum(i + dx[k], j + dy[k]));
                }
            }
        }
    }
    for(i=1;i<=n*m;++i){
        vis.reset();
        if (match(i)) {
            ++ans;
        }
    }

    cout << ans << endl;
	return 0;
}
