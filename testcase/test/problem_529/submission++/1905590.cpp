#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int t;
char s[1000010];

int main()
{
	scanf("%d",&t);
	while (t --)
	{
		bool fl = false,fl2 = false;
		scanf("%s",s + 1);
		int n = strlen(s + 1);
		for (int i = 1;i < n;i ++)
			if (s[i] == 'N' && s[i + 1] == 'N') fl = true;
			else if (s[i] == 'N') fl2 = true;
		if (s[n] == 'N') fl2 = true;
		if (fl || !fl2)
		{
			printf("0 0\n");
			continue;
		}
		if (s[1] == 'V') printf("1 0\n");
		else printf("1 1\n");
	}
}