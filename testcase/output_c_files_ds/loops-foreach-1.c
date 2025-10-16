void func() {
    char list[5][6] = {{'R','e','d','\0'},{'G','r','e','e','n','\0'},{'B','l','u','e','\0'},{'B','l','a','c','k','\0'},{'W','h','i','t','e','\0'}};
    int ix;
    for(ix = 0; ix < 5; ix = ix + 1) {
        int j;
        for(j = 0; list[ix][j] != '\0'; j = j + 1) {
            char c = list[ix][j];
        }
    }
    return;
}
