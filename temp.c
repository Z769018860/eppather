void f(int flag1, int flag2) {
    int i;
    int *a;
    for (i=0;i<3;i=i+1)
{
    if (flag1) {
        if (flag2) {
            a[i] = 0;
        }
        a[i+1] = 0;
    } else {
        a[i+2] = 0;
    }    
}

}
