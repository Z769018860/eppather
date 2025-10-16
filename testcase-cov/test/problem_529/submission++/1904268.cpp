#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T;
char s[N],t[N];

int main(){
	int n;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		int a,b;
		a=b=1;
		
		for(int i=1;i<=n;i++)t[i]=s[i];
		int kk=1;
		while(kk<=n&&t[kk]=='V')kk++;
		if(kk>n)a=0;
		for(int i=kk;i<=n;){
			if(t[i]=='V'){
				if(i<n&&t[i+1]=='N'){
					i=i+1;
				}else {
					a=0;
					break;
				}
			}else{
				if(i==n)break;
				if(t[i+1]=='N'){
					a=0;
					break;
				}
				if(i<n-1&&t[i+2]=='N'){
					i=i+2; 
				}else{
					i=i+1;
					t[i]='N';
				}
			}
		}
		
		for(int i=1;i<=n;i++)t[i]=s[i];
		for(int i=1;i<=n;){
			if(t[i]=='V'){
				b=0;
				break;
			}else{
				if(i==n)break;
				if(t[i+1]=='N'){
					b=0;
					break;
				}
				if(i<n-1&&t[i+2]=='N'){
					i=i+2; 
				}else{
					i=i+1;
					t[i]='N';
				}
			}
		}
		
		printf("%d %d\n",a,b);
	} 
	
	return 0;
}
