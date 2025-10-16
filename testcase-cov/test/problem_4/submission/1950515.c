#include <stdio.h>
#define c "#include <stdio.h>%c#define c %c%s%c%cint main() %c{%c    printf(c, 10, 34, c, 34, 10, 10, 10, 10);%c}"
int main() 
{
    printf(c, 10, 34, c, 34, 10, 10, 10, 10);
}