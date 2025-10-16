#include<cstdio>
#include<cstring>
#define UP(i,a,b) for(i=a;i<=(b);++i)
#define DN(i,a,b) for(i=a;i>=(b);--i)


const int N=1e6+5;
char a[N],b[N];
int fail[N],la,lb,ans;

int main(){
	int i,j;
	scanf("%s%s",a+1,b+1);
	la=strlen(a+1);
	lb=strlen(b+1);
	j=0;
	UP(i,2,lb){
		while(j&&b[i]!=b[j+1]){
			j=fail[j];
		}
		j+=(b[i]==b[j+1]);
		fail[i]=j;
	}
	j=0;
	UP(i,1,la){
		while(j&&a[i]!=b[j+1]){
			j=fail[j];
		}
		j+=(a[i]==b[j+1]);
		if(j==lb){
			++ans;
			j=fail[j];
		}
	}
	printf("%d\n",ans);
	return 0;
}