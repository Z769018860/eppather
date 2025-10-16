#include<bits/stdc++.h>
#define ffor(i,l,r) for(int i=(l),i##_end=(r);i<=i##_end;i++)
using namespace std;

const int INF = 1e8;

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
bool vis[2000005];
unsigned int bae = 0;
bool in[2000005];
unsigned int  getB(){
	while(vis[bae]) 
		bae++;
	return bae;
}
deque<unsigned int> thro; 
deque<unsigned int> uhro;
int main(){
    static int p[2000005];
    int T;read(T);
    int m,a,b,d;
    while(T--){
        unsigned int ans_sum=0,cur_ans=0;
        init_case(m,a,b,d,p);
        memset(vis,0,sizeof(vis));
        memset(in,0,sizeof(in));
        ffor(i,0,a) vis[i] = in[i] = 1;
        thro.clear();
        uhro.clear();
        bae = 0;
		auto calcAns = [&]()->void{
			cur_ans = min(getB(),uhro.size()?uhro.front():INF);
		};
        auto case3 = [&](int x)->void{
			if(thro.empty()||d) return;
            int u = thro.front();
            thro.pop_front();
			in[u] = 1;
			if(uhro.size()&&u==uhro.front()) uhro.pop_front();
			calcAns();
		};
        for(int i=1;i<=m;i++){
            auto x = p[i];
            cur_ans = 0;
            if(x==-1){
            	case3(x);
			}else if(!vis[x]){
				vis[x] =in[x]= 1;
				calcAns();
			}else if(in[x]&&d!=1){
				in[x] = 0;
				thro.push_back(x);
				while(uhro.size()&&uhro.back()>x) uhro.pop_back();
				uhro.push_back(x);
				calcAns();
			}else{
				case3(x);
			} 
            update_ans(ans_sum,cur_ans,i);
        }
        printf("%u\n",ans_sum);
    }
    return 0;
}