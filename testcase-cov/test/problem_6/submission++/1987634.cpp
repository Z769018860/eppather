#include<bits/stdc++.h>
#include "interaction.h"
using namespace std;
vector<int>vec;
int main() {
	int n=get_num();
	for(int i=0;i<n;i++) {
		int l=0,r=1000000;
		while(l<=r) {
			int mid=l+r>>1;
			int x=guess(i,mid);
			if(x==-1) l=mid+1;
			if(x==1)r=mid-1;
			if(x==0){
				vec.push_back(mid);
				break;
			}
			if(l==r){
				vec.push_back(l);
				break;
			}
		}
	}
	submit(vec);
}