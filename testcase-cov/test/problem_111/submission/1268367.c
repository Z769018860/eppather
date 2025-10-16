#include<stdio.h>
#include<string.h>
#define Maxn 2000005
char a[Maxn];
int n,f[Maxn][25],rank[Maxn],tp1[Maxn],tp2[Maxn];
int sa[Maxn],t[Maxn],num1[Maxn];
int num2[Maxn],sum[Maxn],now[Maxn],cnt;
int main(){
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;i++){
        t[a[i]-'0'+1]++;
    }
    for(int i=1;i<=200;i++){
        t[i]+=t[i-1];
        sum[i]=t[i-1]+1;
    }
    for(int i=n;i>=1;i--){
        rank[i]=sum[a[i]-'0'+1];
        sa[t[a[i]-'0'+1]--]=i;
    }
    for(int j=1;(1<<j)<=n;++j){
        for(int i=1;i<=n;++i){
            tp1[i]=num1[i]=rank[i];t[i]=0;
            num2[i]=rank[i+(1<<(j-1))];
        }
        for(int i=1;i<=n;++i)t[num2[i]]++;
        for(int i=1;i<=n;++i){
			t[i]+=t[i-1];sum[i]=t[i-1]+1;}
        for(int i=n;i>=1;--i){
			tp2[sa[i]]=rank[sa[i]]=sum[num2[sa[i]]];now[t[num2[sa[i]]]--]=sa[i];}
        for(int i=1;i<=n;++i){
			sa[i]=now[i];t[i]=0;}
        for(int i=1;i<=n;++i)
			t[num1[i]]++;
        for(int i=1;i<=n;++i){
			t[i]+=t[i-1];sum[i]=t[i-1]+1;}
        for(int i=n;i>=1;--i){
			rank[sa[i]]=sum[num1[sa[i]]];now[t[num1[sa[i]]]--]=sa[i];}
        for(int i=1;i<=n;++i){
		sa[i]=now[i];}
        cnt=0;
        for(int i=1;i<=n;++i){
            if(tp1[sa[i]]==tp1[sa[i-1]]){
                if(tp2[sa[i]]==tp2[sa[i-1]])rank[sa[i]]=rank[sa[i-1]];
                else rank[sa[i]]=i,cnt++;
            }
            else{
                rank[sa[i]]=i,cnt++;
            }
        }
        if(cnt>=n)break;
    }
    for(int i=1;i<=n;i++){
        printf("%d ",sa[i]);
    } 
    return 0;
}
