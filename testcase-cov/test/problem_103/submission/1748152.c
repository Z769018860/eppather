#include<stdio.h>
#include<math.h>
#include<string.h>
int n[1000100],len1,len2;
char a[1000100],b[1000100];
void kmp()
{
    int  j=0,i=0;
    int ans=0;
    while(i<len1)
    {
        if(j==-1||a[i]==b[j])
        {
			++i;++j;
		}  
        else
          j=n[j];
        if(j==len2)
        {
		    j=n[j];    
            ans++;
        }
    }
    printf("%d\n",ans);
}
main()
{
    scanf("%s %s",a,b);
    len1=strlen(a);    
    len2=strlen(b);     
    if(len2>len1)
        printf("0\n");
    int j=-1,i=0;
    n[0]=-1;
    while(i<len2)
    {
        if(j==-1||b[i]==b[j])
        {
            i++;j++;         
            n[i]=j;     
        }
        else
          j=n[j];
    }
    kmp();
    return 0;
}
