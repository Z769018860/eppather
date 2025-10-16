#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<cctype>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using std::min;
using std::max;
using std::swap;
using std::vector;
const int N=1e6+5;
typedef double db;
typedef long long ll;
typedef unsigned int uint;
#define pb(A) push_back(A)
#define pii std::pair<int,int>
#define all(A) A.begin(),A.end()
#define mp(A,B) std::make_pair(A,B)

uint ans,now;
int ptr,hd,tail,q[N][2];
int T,m,a,b,d,p[N],remm[N];
int hasbuy[N<<1],isin[N<<1];

namespace IO{
    int c;
    unsigned int seed;
    unsigned int randnum(){
        seed^=seed<<13;
        seed^=seed>>17;
        seed^=seed<<5;
        return seed;
    }

    inline int read(int &x){scanf("%d",&x);return x;}
    inline void init_case(int &m,int &a,int &b,int &d,int p[]){
        scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
        for(int i=1;i<=m;i++){
            if(randnum()%c==0)p[i]=-1;
            else p[i]=randnum()%b;
        }
    }

    inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
        const static unsigned int mod=998244353;
        ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
    }
}
using IO::read;
using IO::init_case;
using IO::update_ans;

int getint(){
    int X=0,w=0;char ch=0;
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=X*10+ch-48,ch=getchar();
    if(w) return -X;return X;
}

void rem(int x){
	isin[remm[x]]=1;
	while(hd<=tail and q[hd][1]<=x) hd++;
}

signed main(){
    read(T);
    while(T--){
    	ans=now=0;
    	int cnt1=0,cnt2=0;
    	memset(isin,0,sizeof isin);
    	memset(hasbuy,0,sizeof hasbuy);
    	init_case(m,a,b,d,p);
    	for(int i=0;i<=a;i++) isin[i]=hasbuy[i]=1;
    	ptr=a+1;hd=1,tail=0;
    	for(int i=1;i<=m;i++){
    		if(p[i]==-1){
    			if(d or hd>tail) continue;
    			cnt1++;rem(cnt1);
    			while(isin[ptr]) ptr++;
			} else if(!hasbuy[p[i]]){
				isin[p[i]]=hasbuy[p[i]]=1;
				while(isin[ptr]) ptr++;
			} else if(isin[p[i]]){
				if(d) continue;
				cnt2++;remm[cnt2]=p[i];
				while(hd<=tail and q[tail][0]>p[i]) tail--;
				q[++tail][0]=p[i];q[tail][1]=cnt2;
				isin[p[i]]=0;
				while(isin[ptr]) ptr++;
			} else{
    			if(hd>tail or d) continue;
    			cnt1++;rem(cnt1);
    			while(isin[ptr]) ptr++;
			} now=ptr;
			if(hd<=tail) now=min(now,(uint)q[hd][0]);
			update_ans(ans,now,i);
		} printf("%u\n",ans);
	} return 0;
}
