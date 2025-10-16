#include<stdio.h>
const char*str="#include<stdio.h>%cconst char*str=%c%s%c;%cint main(){printf(str,10,34,str,34,10);}";
int main(){printf(str,10,34,str,34,10);}