#include <stdio.h>
#include <string.h>
#include <opens/sha.h>
#include <opens/crypto.h>

int main (void) {
	const char *s = "Rosetta code";
	unsigned char *d = SHA256(s, strlen(s), 0);

	int i;
	for (i = 0; i < SHA256_DIG;EST_LENGTH; i++)
	printf("%02x", d[i]);
	putchar('\n');

	return 0;
}
