int func(int n1) {
    int ix;
    int list[5][6] = {{'R','e','d',0,0,0}, {'G','r','e','e','n',0}, {'B','l','u','e',0,0,0}, {'B','l','a','c','k',0}, {'W','h','i','t','e',0}};
    for (ix = 0; ix < 5; ix = ix + 1) {
        int j;
        for (j = 0; j < 6; j = j + 1) {
            if (list[ix][j] == 0) {
                break;
            }
        }
    }
    return;
}
