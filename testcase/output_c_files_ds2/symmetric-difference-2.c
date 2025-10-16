void symmdiff(int* sym_size, int f, const char* setA[4], int setAsize, const char* setB[4], int setBsize)
{
    int union_size;
    int max_union_size;
    int diff_size;
    const char* union_set[8];
    int union_xor[8];
    int ix;
    int ixu;
    const char* diff_set[8];
    int n;
    
    max_union_size = setAsize + setBsize;
    for (ix = 0; ix < setAsize; ix = ix + 1) {
        union_set[ix] = setA[ix];
        union_xor[ix] = 1;
    }
    diff_size = union_size = setAsize;
    for (ix = 0; ix < setBsize; ix = ix + 1) {
        for (ixu = 0; ixu < union_size; ixu = ixu + 1) {
            if (union_set[ixu] == setB[ix]) {
                break;
            }
        }
        if (ixu < union_size) {
            union_xor[ixu] = 1 - union_xor[ixu];
            diff_size = diff_size - 1;
        } else {
            if (f == 1) {
                union_set[ixu] = setB[ix];
                union_xor[ixu] = 1;
                union_size = union_size + 1;
                diff_size = diff_size + 1;
            }
        }
    }
    n = 0;
    for (ixu = 0; ixu < union_size; ixu = ixu + 1) {
        if (union_xor[ixu]) {
            diff_set[n] = union_set[ixu];
            n = n + 1;
        }
    }
    *sym_size = diff_size;
    return;
}
