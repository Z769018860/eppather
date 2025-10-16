int foo(int n1, int n2) {
    int st_size[5];
    st_size[0] = 0;
    st_size[1] = 0;
    st_size[2] = 0;
    st_size[3] = 0;
    st_size[4] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        st_size[i] = st_size[i] + 1;
    }
    return;
}
