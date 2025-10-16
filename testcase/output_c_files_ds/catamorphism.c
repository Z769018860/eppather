int reduce_add_sub_mul(int size, int elms[5])
{
    int val_add;
    int val_sub;
    int val_mul;
    int i;
    val_add = elms[0];
    val_sub = elms[0];
    val_mul = elms[0];
    
    for (i = 1; i < size; i = i + 1)
    {
        val_add = val_add + elms[i];
        val_sub = val_sub - elms[i];
        val_mul = val_mul * elms[i];
    }
    
    return val_add + val_sub + val_mul;
}
