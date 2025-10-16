#include <stdio.h>

char s[10010]; 

int main() { FILE *in, *out;

if ((in = fopen("copycat.in", "r")) == NULL)
{
	printf("Read file error!");
}
if ((out = fopen("copycat.out", "w")) == NULL)
{
	printf("Write file error");
}

int T = 0;
char ch;
while ((ch = getc(in)) != '\n')
{
	T = T * 10 + (ch - '0');
}

while (T --)
{
	fgets(s, 10005, in);
	fprintf(out, "%s", s);
}

return 0;
}