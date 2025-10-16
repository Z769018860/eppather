#include<stdio.h>
#include<string.h>
#define N 1000005
char s[N];
int n,sa[N],rnk[N],c[N],xx[N],yy[N];
int cmp(int *y,int i,int j,int k){
	int xl=y[i],xr=i+k<n?y[i+k]:-1;
	int yl=y[j],yr=j+k<n?y[j+k]:-1;
	return xl==yl&&xr==yr;
}
void suffix_array(int m){
	int *x=xx,*y=yy,*t;
	for(int i=0;i<m;i++){
		c[i]=0;
	}
	for(int i=0;i<n;i++){
		c[x[i]=s[i]]++;
	}
	for(int i=1;i<m;i++){
		c[i]+=c[i-1];
	}
	for(int i=0;i<n;i++){
		sa[--c[x[i]]]=i;
	}
	for(int k=1;k<n;k<<=1){
		int p=0;
		for(int i=n-k;i<n;i++){
			y[p++]=i;
		}
		for(int i=0;i<n;i++){
			if(sa[i]>=k){
				y[p++]=sa[i]-k;
			}
		}
		for(int i=0;i<m;i++){
			c[i]=0;
		}
		for(int i=0;i<n;i++){
			c[x[y[i]]]++;
		}
		for(int i=1;i<m;i++){
			c[i]+=c[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--c[x[y[i]]]]=y[i];
		}
		t=x;
		x=y;
		y=t;
		x[sa[0]]=0;
		m=1;
		for(int i=1;i<n;i++){
			x[sa[i]]=cmp(y,sa[i-1],sa[i],k)?m-1:m++;
		}
		if(n==m){
			break;
		}
	}
}
int main(){
	scanf("%s",s);
	n=strlen(s);
	suffix_array(128);
	for(int i=0;i<n;i++){
		printf("%d%c",sa[i]+1," \n"[i==n-1]);
	}
	return 0;
}