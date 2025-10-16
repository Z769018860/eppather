int func(int argc, int argv[5]) {
    int foo[5];
    foo[0] = 97;
    int pi[5];
    pi[0] = 3;
    int minsize[5];
    minsize[0] = 10;
    int maxsize[5];
    maxsize[0] = 10;
    int ptrToConst[5];
    int constPtr[5];
    int constPtrToConst[5];
    for (int i = 0; i < 5; i = i + 1) {
        ptrToConst[i] = 0;
        constPtr[i] = 0;
        constPtrToConst[i] = 0;
    }
    return;
}
