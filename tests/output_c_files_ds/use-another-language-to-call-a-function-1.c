int Query(char* Data, unsigned* Length) {
    int i;
    for (i = 0; i < *Length; i = i + 1) {
        Data[i] = 0;
    }
    *Length = 0;
    return 0;
}
