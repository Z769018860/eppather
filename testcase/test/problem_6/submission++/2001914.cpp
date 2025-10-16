#include<cstdio>
#include<vector>
#include"interaction.h"
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)

using std::vector;

int n;
vector<int> a;

int main(){
	int i,l,r,mid,k;
	n=get_num();
	UP(i,0,n-1){
		l=0;r=1e6;
		while(l<=r){
			mid=(l+r)>>1;
			k=guess(i,mid);
			if(k==-1){
				l=mid+1;
			}else if(k==0){
				a.push_back(mid);
				break;
			}else{
				r=mid-1;
			}
		}
	}
	submit(a);
	return 0;
}