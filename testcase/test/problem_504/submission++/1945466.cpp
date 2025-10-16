#include<vector>
#include<iostream>
#include<cstdlib>
#include<limits.h>
#include<queue>

using namespace std;

#define int long long

vector<int> values;

namespace tree{
	struct node{
		int from,to;
		int lson,rson;
		int minvalue,minnum;
		int k;
		
		node(){
			from=to=lson=rson=0;
			minvalue=LONG_LONG_MAX;
			minnum=0;
			k=0;
		}
	};
	
	struct tree{
		vector<node> work;
		
		void pushup(int num){
			if(work[work[num].lson].minvalue<work[work[num].rson].minvalue){
				work[num].minvalue=work[work[num].lson].minvalue;
				work[num].minnum=work[work[num].lson].minnum;
			}
			else{
				work[num].minvalue=work[work[num].rson].minvalue;
				work[num].minnum=work[work[num].rson].minnum;
			}
		}
		void build(int num,int l,int r){
			work[num].from=l,work[num].to=r;
			if(l==r){
				work[num].minvalue=values[l];
				work[num].minnum=l;
				
				return;
			}
			node emp;
			work.push_back(emp);
			work[num].lson=work.size()-1;
			work.push_back(emp);
			work[num].rson=work.size()-1;
			build(work[num].lson,l,(l+r)/2);
			build(work[num].rson,(l+r)/2+1,r);
			pushup(num);
			
		}
		tree(int n){
			work.resize(2);
			build(1,1,n);
		}
		void pushdown(int num){
			if(work[num].k!=0&&work[num].lson!=0){
				work[work[num].lson].minvalue=max(work[work[num].lson].minvalue,work[num].k);
				work[work[num].lson].k=max(work[work[num].lson].k,work[num].k);
				work[work[num].rson].minvalue=max(work[work[num].rson].minvalue,work[num].k);
				work[work[num].rson].k=max(work[work[num].rson].k,work[num].k);
			}
		}
		void update(int num,int l,int r,int k){
			if(l>work[num].to||r<work[num].from){
				return;
			}
			if(l<=work[num].from&&work[num].to<=r){
				work[num].minvalue=max(work[num].minvalue,k);
				work[num].k=max(work[num].k,k);
				return;
			}
			pushdown(num);
			update(work[num].lson,l,r,k);
			update(work[num].rson,l,r,k);
			pushup(num);
		}
		pair<int,int> ask(int num,int l,int r){
			if(l>work[num].to||r<work[num].from){
				return make_pair(-1,LONG_LONG_MAX);
			}
			if(l<=work[num].from&&work[num].to<=r){
				return make_pair(work[num].minnum,work[num].minvalue);
			}
			pushdown(num);
			pair<int,int> ask1=ask(work[num].lson,l,r),ask2=ask(work[num].rson,l,r);
			if(ask1.second<ask2.second){
				return ask1;
			}
			else{
				return ask2;
			}
		}
	};
}

struct date{
	int l,r,x,v;
	
	date(){}
	date(int ll,int rr,int xx,int vv){
		l=ll,r=rr,x=xx,v=vv;
	}
};

date make_date(int a,int b,int c,int d){
	date ret(a,b,c,d);
	return ret;
}

bool operator < (date a,date b){
	return a.v>b.v;
}

signed main(){
	
	
	int n;
	cin>>n;
	values.resize(n+1);
	for(int i=1;i<=n;i++){
		cin>>values[i];
	}
	
	tree::tree work(n);
	
	int m;
	cin>>m;
	while(m--){
		int op;
		cin>>op;
		if(op==1){
			int a,b,k;
			cin>>a>>b>>k;
			work.update(1,a,b,k);
		}
		else if(op==2){
			int l,r,value,time;
			cin>>l>>r>>value>>time;
			if(time>r-l+1){
				cout<<-1<<"\n";
				continue;
			}
			auto tmp1=work.ask(1,l,r);
			date init=make_date(l,r,tmp1.first,tmp1.second);
			priority_queue<date> Do;
			while(!Do.empty()){
				Do.pop();
			}
			Do.push(init);
			vector<int> answers;
			answers.clear();
			while(time--){
				if(Do.empty()){
					cout<<-1<<"\n";
					goto label;
				}
				date front=Do.top();
				Do.pop();
				if(front.x==-1){
					exit(-1);
				}
				
				if(front.v>=value){
					cout<<-1<<"\n";
					goto label;
				}
				answers.push_back(front.v);
				if(front.x>l){
					auto tmp2=work.ask(1,front.l,front.x-1);
					
					Do.push(make_date(front.l,front.x-1,tmp2.first,tmp2.second));
				}
				if(front.x<r){
					auto tmp3=work.ask(1,front.x+1,front.r);
					auto tmp11=make_date(front.x+1,front.r,tmp3.first,tmp3.second);
					
					Do.push(tmp11);
				}
			}
			for(auto i:answers){
				cout<<i<<" ";
			}
			cout<<"\n";
			label:;
		}
	}
}