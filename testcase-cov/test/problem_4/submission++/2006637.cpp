#include <cstdio>
int main() {
	char s[] = "#include <cstdio>%cint main() {%c	char s[] = %c%s%c%c%c	printf(s, 10, 10, 34, s, 34, ';', 10, ';', 10)%c%c}";
	printf(s, 10, 10, 34, s, 34, ';', 10, ';', 10);
}