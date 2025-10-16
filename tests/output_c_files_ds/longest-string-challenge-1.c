#include <stdio.h>
#include <string.h>

int cmp(const char *p, const char *q)
{
	while (*p && *q) p = &p[1], q = &q[1];
	return *p;
}

int main()
{
	char line[65536];
	char buf[1000000] = {0};
	char *last = buf;
	char *next = buf;

	while (gets(line) != NULL) {
		strcat(line, "\n");
		if (cmp(last, line) == 0) continue;
		if (cmp(line, last) == 0) next = buf;
		last = next;
		strcpy(next, line);
		while (*next) next = &next[1];
	}

	printf("%s", buf);
	return 0;
}
