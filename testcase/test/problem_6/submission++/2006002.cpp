#include<bits/stdc++.h>
#include"interaction.h"
using namespace std;
int main(){
	int n=get_num();
	vector<int> ans;
	for(int i=0;i<n;i++){
		int l=0,r=1e6;
		while(l<=r){
			int mid=(l+r)>>1,moo=guess(i,mid);
			if(!moo){ans.push_back(mid);break;}
			if(moo==1)r=mid-1;
			else l=mid+1;
		}
	}
	submit(ans);
	return 0;
}