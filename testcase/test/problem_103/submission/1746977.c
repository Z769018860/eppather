#include<stdio.h>
#include<string.h>
int ne[2000000];
char s[2000000],p[2000000];
int s1,p1;
void jun()
{
	int i,j;
	i=0,j=-1;
	ne[0]=-1;
	while(i<p1){
		if(j==-1||p[i]==p[j])
		{
			i++;
			j++;
			ne[i]=j;
		}
		else
			j=ne[j];
	}
}
int main()
{
int i,j;
int count;
gets(s);
gets(p);
s1=strlen(s);
p1=strlen(p);
jun();


j=0;count=0;i=0;	 
while(i<s1){	 
	if(j==-1||s[i]==p[j])
	{
		j++;
		i++;
	}
	else
	{
		j=ne[j];
	}
	if(j==p1){
		j=ne[j];
		count++;
	}
}
printf("%d\n",count);
return 0;
}
