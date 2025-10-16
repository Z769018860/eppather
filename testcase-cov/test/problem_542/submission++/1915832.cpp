#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
using namespace std;
const int maxn=1005;
int n,k,p[1000005],g0[1000005],cv[1000005],cnt,St[maxn],Ed[maxn];
int st[maxn],ed[maxn],c1[maxn],c2[maxn],L,R;
pair<int,int> sk[1000005];
void fil1(int l,int r){
	printf("%d %d ",k,l);
	for(int i=l,j=0;i<=r;++i)if(j<k-2){
		if(cv[i]){
			cv[i]=0;
			++j;
			printf("%d ",i);
		}
	}
	printf("%d\n",r);
}
void fil2(int l,int r,int l_){
	cnt=0;
	for(int i=l,j=2;i<=r;++i)if(cv[i]){
		if(j==k){
			if(i>=l_)break;
			else j=0;
		}
		cv[i]=0;
		++j;
		sk[++cnt].first=i;
	}
	
	printf("%d %d ",cnt+2,l);
	for(int i=1;i<=cnt;++i)printf("%d ",sk[i].first);
	printf("%d\n",r);
}
signed main(){
	
	scanf("%d",&n);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&p[i]);
		if(p[i]%k)p[i]=cv[i]=1;
		else p[i]=0,g0[++cnt]=i;
	}
	if(cnt<2*k||p[1]||p[n]||n%k||n<k*k){
		printf("No");
		return 0;
	}
	for(int i=1;i<=k;++i)St[i]=g0[i];
	for(int i=cnt-k+1;i<=cnt;++i)Ed[i-(cnt-k)]=g0[i];
	
	for(int i=k+1;i<=cnt-k;++i)p[g0[i]]=cv[g0[i]]=1;
	for(int i=1;i<=n;++i)p[i]+=p[i-1];
	for(int i=1;i<=k;++i){
		for(int j=0;j<=i;++j)st[j]=p[St[j+1]];
		for(int j=k-i;j<=k;++j)ed[j-(k-i)]=p[Ed[j]]-(k-2)*(k-i);
		for(int j=0;j<=i;++j)c1[j]=c2[j]=0;
		if(i==k)st[i]=ed[0]=st[k-1],c1[i]=c2[0]=1;
		L=1;R=0;
		for(int j=k;j>=1;--j){
			int x=St[j]-j*(k-1);
			if(L<=R&&sk[L].first>=j+(k-i))++L;
			while(L<=R&&sk[R].second<=x)--R;
			sk[++R]=make_pair(j,x);
			if(j<=i+1&&L==R)c1[j-1]=1;
		}
		L=1;R=0;
		for(int j=1;j<=k;++j){
			int x=Ed[j]-j*(k-1);
			if(L<=R&&sk[L].first<=j-(k-i))++L;
			while(L<=R&&sk[R].second>=x)--R;
			sk[++R]=make_pair(j,x);
			if(j>=k-i&&L==R)c2[j-(k-i)]=1;
			
		}
		R=0;
		for(int j=1;j<=i;++j){
			int x=ed[j]-(k-2)*j;
			while(R&&sk[R].first>=x)--R;
			sk[++R]=make_pair(x,j);
			
		}
		
		
		sk[0].second=-1;
		int nw=0;
		for(int j=0,u=0;j<=i;++j){
			if(j>0){
				int x=st[j]-(k-2)*j;
				if(x<=0)x=0;
				else x=(x-1)/k*k+k;
				nw=max(nw,(lower_bound(sk+1,sk+R+1,make_pair(x,0))-1)->second+1);
				
			}
			
			if(c1[j]){
				while(u<=i&&(st[j]>ed[u]||!c2[u]))++u;
				if(u>i)break;
				if(st[j]==ed[u]&&u>=nw){
					
					printf("Yes\n%d\n",k);
					
					
					for(int g=1;g<=k-i;++g)fil1(St[j+g],Ed[u+g]);
					St[k+1]=n+1;cv[n+1]=1;
					for(int g=0,A=0,B=0;g<=i;++g){
						int tmp=A+1;
						if(tmp==j+1)tmp=j+k-i+1;
						
						if(g)fil2(St[A],Ed[B],St[tmp]);
						A=tmp;
						tmp=B+1;
						if(tmp==u+1)tmp=u+k-i+1;
						B=tmp;
					}
					return 0;
				}
			}
		}
	}
	printf("No");
	return 0;
}