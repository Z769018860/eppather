#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	printf("%d\n",(n*n+1)/2);
	if(n&1){
		for(int i=0;i<n;i+=2)
			for(int j=0;j<n;j+=2){
				printf("%d %d ",i+1,j+1);
				if(i+j<n) printf("%d\n",i+j+1);
				else printf("%d\n",i+j-n);
			}
		for(int i=1;i<n;i+=2)
			for(int j=1;j<n;j+=2){
				printf("%d %d ",i+1,j+1);
				if(i+j<=n) printf("%d\n",i+j);
				else printf("%d\n",i+j-n+1);
			}
	}
	else{
		for(int i=0;i<n;i+=2)
			for(int j=0;j<n;j+=2)
				printf("%d %d %d\n",i+1,j+1,(i+j)%n+1);
		for(int i=1;i<n;i+=2)
			for(int j=1;j<n;j+=2)
				printf("%d %d %d\n",i+1,j+1,(i+j+n-1)%n+1);
	}
	return 0;
}
