#include<stdio.h>
#include<string.h>

const int N =1e6+10;

char s[1000010],p[1000010];
int ne[1000010];
int slen,plen;















int KMP()
{
	plen=strlen(p+1);
	slen=strlen(s+1);
	int ans=0;
	for (int i = 2, j = 0; i <= plen; i ++ )
	{
	    while (j && p[i] != p[j + 1]) j = ne[j];
	    if (p[i] == p[j + 1]) j ++ ;
	    ne[i] = j;
	}
	
	
	for (int i = 1, j = 0; i <= slen; i ++ )
	{
	    while (j && s[i] != p[j + 1]) j = ne[j];
	    if (s[i] == p[j + 1]) j ++ ;
	    if (j == plen)
	    {
	        j = ne[j];
	        ans++;
	        
	    }
	}
	return ans;
}





















int main()
{
	while(~scanf("%s%s",s+1,p+1))
	{
		printf("%d\n",KMP());	
	}
	return 0;	
} 