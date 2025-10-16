void getWindowCoords(int* childx, int* childy) {
    int x[5];
    int y[5];
    int mask[5];
    int props[5];
    int n_items[5];
    int bytes_after_ret[5];
    int atom_type_prop[5];
    int actual_format[5];
    
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        props[x[0]] = 0;
    }
    
    for (y[0] = 0; y[0] < 5; y[0] = y[0] + 1) {
        mask[y[0]] = 0;
    }
    
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        n_items[x[0]] = 0;
    }
    
    for (y[0] = 0; y[0] < 5; y[0] = y[0] + 1) {
        bytes_after_ret[y[0]] = 0;
    }
    
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        atom_type_prop[x[0]] = 0;
    }
    
    for (y[0] = 0; y[0] < 5; y[0] = y[0] + 1) {
        actual_format[y[0]] = 0;
    }
    
    childx[0] = 0;
    childy[0] = 0;
    
    return;
}
