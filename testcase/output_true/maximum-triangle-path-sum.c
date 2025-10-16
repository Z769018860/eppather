int triangle_path(int tri[120], int len, int base)
{
    int step = base - 1;
    int stepc = 0;
    int i;
    int temp1;
    int temp2;
    
    for (i = len - base - 1; i >= 0; i = i - 1) {
        temp1 = tri[i + step];
        temp2 = tri[i + step + 1];
        if (temp1 > temp2) {
            tri[i] = tri[i] + temp1;
        } else {
            tri[i] = tri[i] + temp2;
        }
        stepc = stepc + 1;
        if (stepc == step) {
            step = step - 1;
            stepc = 0;
        }
    }
    return;
}
