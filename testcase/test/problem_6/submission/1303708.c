#include <stdio.h>
int main()
{
	int n,low,high,mid,num=0,a[100],res,i;
	low=1;
	high=1000000;
	mid=(high+low)/2;
    printf("get_num\n");
    fflush(stdout);
	scanf("%d",&n);
	while(num!=n)
{
	printf("guess %d %d\n",num,mid);
	fflush(stdout);
	scanf("%d",&res);
	if(res==1)
	{
		high=mid;
		mid=(high+low)/2;
	}
	if(res==-1)
	{
		low=mid;
		mid=(high+low)/2;
	}
	if(res==0)
	{
		a[num]=mid;
		num++;
	    low=0;
	    high=1000000;
	    mid=(high+low)/2;
		continue;
	}
	if(high-low<=2)
	{
		for(i=low;i<high;i++)
		{
			printf("guess %d %d\n",num,i);
			fflush(stdout);
			scanf("%d",&res);
			if(res==0)
			{
				a[num]=i;
				num++;
				low=1;
	            high=1000000;
	            mid=(high+low)/2;
				break;
			}
		}
	}
}
	if(num==n)
	{
		printf("submit ");
		for(i=0;i<n;i++)
		{
			printf("%d ",a[i]);
		}
	}
}