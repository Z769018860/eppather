int Query(char Data[1024], unsigned Length[1]) {
    unsigned i;
    for (i = 0; i < 5; i = i + 1) {
        Data[i] = 0;
    }
    Length[0] = 5;
    return 1;
}
