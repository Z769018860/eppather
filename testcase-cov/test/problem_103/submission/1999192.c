#include<stdio.h>
#include<string.h>
void prefix_table(char subs[],int next[],int len)
{
	next[0]=-1;
	int k=-1,j=0;
	while(j<len)
	{
		if(k==-1||subs[j]==subs[k])
		{
			k++;
			j++;
			next[j]=k;
		}
		else
			k=next[k];
	}
}
int kmp(char str[],char subs[])
{
	int len1=strlen(str),len2=strlen(subs),i=0,j=0,cnt=0;
	int next[len2];
	prefix_table(subs,next,len2);
	while(i<len1)
	{
		if(j==-1||str[i]==subs[j])
		{
			i++;
			j++;
		}
		else
			j=next[j];
		if(j==len2)
		{
			cnt++;
			j=next[j];
		}
	}
	return cnt;
}
int main()
{
	char a[1000001],b[1000001];
	gets(a);
	gets(b);
	int n;
	n=kmp(a,b);
	printf("%d",n);
} 