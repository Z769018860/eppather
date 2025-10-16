#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pr;
const int mod=998244353;
int n,a[300005],q,R[300005][2],sge[300005],sle[300005],in[300005];
int fl[300005],fr[300005],st[300005],top,d[300005];
vector<int> g[300005],isl[300005];
pr operator +(pr x,pr y){
	return pr(x.first+y.first,x.second+y.second);
}
pr operator -(pr x,pr y){
	return pr(x.first-y.first,x.second-y.second);
}
struct ZXS{
	int ls[6000005],rs[6000005],tot,rt[300005];
	pr sum[6000005];
	void Insert(int &p,int q,int l,int r,int x){
		p=++tot,ls[p]=ls[q],rs[p]=rs[q],sum[p]=sum[q]+pr(1,x);
		if(l==r)return ;
		int mid=(l+r)/2;
		if(x<=mid)Insert(ls[p],ls[q],l,mid,x);
		else Insert(rs[p],rs[q],mid+1,r,x);
	}
	pr Query(int p,int q,int l,int r,int x,int y) {
		if(!p||q==p)return pr(0,0);
		if(x<=l&&r<=y)return sum[p]-sum[q];
		int mid=(l+r)/2;
		pr ret=pr(0,0);
		if(x<=mid)ret=ret+Query(ls[p],ls[q],l,mid,x,y);
		if(mid<y)ret=ret+Query(rs[p],rs[q],mid+1,r,x,y);
		return ret;
	}
	pr Query(int l1,int r1,int l2,int r2){
		if(l1>r1||l2>r2)return pr(0,0);
		return Query(rt[r1],rt[l1-1],1,n,l2,r2);
	}
}t[2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),fl[i]=fr[i]=i;
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i])top--;
		if(st[top])g[i].push_back(st[top]),g[st[top]].push_back(i);
		fl[i]=min(fl[i],st[top]+1),st[++top]=i;
	}
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]>a[i])top--;
		if(st[top])g[i].push_back(st[top]),g[st[top]].push_back(i);
		fl[i]=min(fl[i],st[top]+1),st[++top]=i;
		isl[fl[i]].push_back(i);
	}
	st[top=0]=n+1;
	for(int i=n;i;i--){
		while(top&&a[st[top]]<a[i])top--;
		if(st[top]!=n+1)g[i].push_back(st[top]),g[st[top]].push_back(i);
		fr[i]=max(fr[i],st[top]-1),st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i;i--){
		while(top&&a[st[top]]>a[i])top--;
		if(st[top]!=n+1)g[i].push_back(st[top]),g[st[top]].push_back(i);
		fr[i]=max(fr[i],st[top]-1),st[++top]=i;
	}
	scanf("%d",&q);
	if(n==1){
		puts("1");
		while(q--)puts("1 1");
		return 0;
	}
	for(int i=1;i<=n;i++){
		sge[i]=sge[i-1]+(a[i]>a[i-1]);
		sle[i]=sle[i-1]+(a[i]<a[i-1]);
	}
	for(int i=1,j=0;i<=n;i++){
		while(j<n&&(sge[j+1]-sge[i]==j+1-i||sle[j+1]-sle[i]==j+1-i))j++;
		R[i][0]=j;
		sort(g[i].begin(),g[i].end());
		g[i].resize(unique(g[i].begin(),g[i].end())-g[i].begin());
	}
	multiset<int> s; 
	int j=1;
	for(int i=1;i<=n;i++){
		for(int l:g[i]){
			if(l<j||l>i){
				d[l]^=1;
				continue;
			}
			if(d[l]&&fl[l]>j&&in[l])s.erase(s.find(fr[l])),in[l]=0;
			d[l]^=1;
			if(d[l]&&fl[l]>j&&!in[l])s.insert(fr[l]),in[l]=1;
		}
		while(s.size()&&i>*s.begin()){
			R[j][1]=i-1;
			
			for(int k:g[j]){
				if(k<j||k>i){
					d[k]^=1;
					continue;
				}
				if(d[k]&&fl[k]>j&&in[k])s.erase(s.find(fr[k])),in[k]=0;
				d[k]^=1;
				if(d[k]&&fl[k]>j&&!in[k])s.insert(fr[k]),in[k]=1;
			}
			for(int k:isl[j+1])if(k>=j&&k<=i&&d[k]&&in[k])s.erase(s.find(fr[k])),in[k]=0;
			j++;
		}
	}
	while(j<=n)R[j][1]=n,j++;
	for(int i=1;i<=n;i++){
		for(int j=0;j<2;j++){
			t[j].rt[i]=t[j].rt[i-1];
			t[j].Insert(t[j].rt[i],t[j].rt[i],1,n,R[i][j]);
		}
	}
	if(R[1][0]==n)puts("2");
	else if(R[1][1]==n)puts("3");
	else puts("4");
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		if(l==r)puts("1 1");
		else {
			if(R[l][0]>=r)printf("%d %lld\n",2,1ll*(r-l+1)*(r-l+2)/2-(r-l+1));
			else if(R[l][1]>=r){
				pr w=t[0].Query(l,r,1,r);
				printf("3 %lld\n",1ll*r*w.first-w.second);
			}
			else {
				pr w=t[1].Query(l,r,1,r);
				printf("4 %lld\n",1ll*r*w.first-w.second);
			}
		}
	}
}