#include<bits/stdc++.h>
#include<regex.h>
#define F(i,j,k) for(auto i=j;i<=(decltype(j))(k);i++)
#define exec(...) [&](){__VA_ARGS__}()
#define view(x) begin(x),end(x)
#define pb push_back
#define lambda [&]
#define x first
#define y second
#define endl '\n'
#define os ostream
using namespace std;
template<typename T>void ckmin(T& a,T b){(a>b)&&(a=b);}
template<typename T>void ckmax(T& a,T b){(a<b)&&(a=b);}

#ifdef DEBUG
template<typename ...T>os& operator<<(os& out,tuple<T...> x);

template<typename T1,typename T2>os& operator<<(os& out,pair<T1,T2> x){return out<<tuple(x);}
template<typename T,typename=decltype(T().begin()),typename=enable_if_t<!is_same_v<decay_t<T>,string>>>os& operator<<(os& out,T x){return out<<"{",exec(auto n=0u;for(auto i:x) out<<i<<(++n==x.size()?"":",");),out<<"}";}
template<typename ...T>os& operator<<(os& out,tuple<T...> x){return apply(lambda(T... xx){auto n=0u;out<<"{";((out<<xx<<(++n==sizeof...(T)?"":",")),...),out<<"}";},x),out;}
#define debug(...) cerr<<"#"<<__LINE__<<": "<<#__VA_ARGS__<<" = "<<tuple(__VA_ARGS__)<<endl
#else
#define debug(...) (void)0
#endif

char p[101],s[101];
regmatch_t m[1];
regex_t r;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	while(cin>>p>>s){
		regcomp(&r,p,1),regexec(&r,s,1,m,0);
		cout<<(regexec(&r,s,1,m,0) || size_t(m->rm_eo - m->rm_so)<strlen(s)?"No":"Yes")<<endl;
		regfree(&r);
	}
    return not "FST";
}