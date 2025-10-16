int func() {
    char c[200] = "#include <stdio.h>%cint main(){char*c=%c%s%c;printf(c,10,34,c,34,10);return 0;}%c";
    return;
}
