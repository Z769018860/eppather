#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
char a[1000010];
char s[1000010];
ull ha[1000010];
int main()
{
    ull hs=0,pow1=1;
    scanf("%s",a);
    scanf("%s",s);
    int b=123,i;
    int la=strlen(a);
    int ls=strlen(s);
    for(i=0;i<ls;i++)
    {
        hs=hs*b+(ull)(s[i]);
        pow1*=b;
    }
    ha[0]=a[0];
    for(i=1;i<la;i++)
        ha[i]=ha[i-1]*b+(ull)(a[i]);
    int k=0;
    for(i=ls-1;i<la;i++)
    {
        if(i-ls<0&&ha[i]==hs)
            k++;
        else if(ha[i]-ha[i-ls]*pow1==hs)
            k++;
    }
    printf("%d\n",k);
    return 0;
}
