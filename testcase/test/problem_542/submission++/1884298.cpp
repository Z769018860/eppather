#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;
const int N=1e6+5;
int T,n,k;
int a[N],cb,id[N],rv[N];
vector<int>ans[N];
priority_queue<pair<int,int> >q1;
queue<int>q2;
void upd(){
	while(!q1.empty()){
		int u=q1.top().second;
		if(ans[u].size()%k==k-1){
			q2.push(u);
			q1.pop();
			continue;
		}else return;
	}
}
int main(){
	scanf("%d%d%d",&T,&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]%k==0)id[i]=++cb;
	}
	if(n%k||cb<2*k||a[1]%k||a[n]%k)return puts("No"),0;
	for(int i=1;i<=n;++i){
		if(id[i]){
			if(id[i]<=k){
				ans[id[i]].push_back(i);
				q1.push(make_pair(1,id[i]));
				continue;
			}else if(id[i]>cb-k){
				upd();
				if(q2.empty())return puts("No"),0;
				int u=q2.front();q2.pop();
				ans[u].push_back(i);
				continue;
			}
		}
		upd();
		if(q1.empty()){
			int u=q2.front();
			q2.pop();
			ans[u].push_back(i);
			q1.push(make_pair(0,u));
		}else{
			int u=q1.top().second;
			q1.pop();
			ans[u].push_back(i);
			q1.push(make_pair(ans[u].size()%k,u));
		}
	}
	puts("Yes");
	printf("%d\n",k);
	for(int i=1;i<=k;++i){
		printf("%d",ans[i].size());
		for(auto v:ans[i])printf(" %d",v);
		putchar(10);
	}
	return 0;
}