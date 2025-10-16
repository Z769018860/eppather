#include<bits/stdc++.h>
using namespace std;
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
deque<unsigned int> dq;
queue<unsigned int> q;
int w[4000005],ans;



int main(){

	static int p[2000005];
	int T;read(T);
	int m,a,b,d;
	while(T--){
		unsigned int ans_sum=0,cur_ans=0;
		init_case(m,a,b,d,p);
		while(!q.empty()) q.pop();
		while(!dq.empty()) dq.pop_back();
		memset(w,0,sizeof(w));b=max(a+1,b);
		if(a!=-1) for(int i=0;i<=a;++i) w[i]=1;
		ans=a+1;
		for(int i=1;i<=m;++i){
			if(p[i]==-1){
				if(q.empty()||d==1) continue;
				int t=q.front();
				w[t]=1;q.pop();
				if(!dq.empty()&&t==dq.front())dq.pop_front();
                cur_ans=ans;if(!dq.empty())cur_ans=min(dq.front(),cur_ans);
			}
			else if(!w[p[i]]){
				w[p[i]]=1;
				while(w[ans]) ans++;
				cur_ans=ans;if(!dq.empty())cur_ans=min(dq.front(),cur_ans);
			}
			else if(w[p[i]]==1){
				if(d==1) continue;
				w[p[i]]=2;q.push(p[i]);
				while(!dq.empty()&&dq.back()>p[i]) dq.pop_back();dq.push_back(p[i]);
				cur_ans=ans;if(!dq.empty())cur_ans=min(dq.front(),cur_ans);
			}
			
			else{
				if(q.empty()||d==1) continue;
				int t=q.front();
				w[t]=1;q.pop();
				if(!dq.empty()&&t==dq.front())dq.pop_front();
                cur_ans=ans;if(!dq.empty())cur_ans=min(dq.front(),cur_ans);
			}
			update_ans(ans_sum,cur_ans,i);
		}
		printf("%u\n",ans_sum);
	}
	return 0;
}

