void xcb_example(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10) {
    int c[5];
    int screen[5];
    int win[5];
    int foreground[5];
    int background[5];
    int e[5];
    int mask[5];
    int values[2];
    int string_len[5];
    int rectangles[4];
    
    mask[0] = 0;
    string_len[0] = 11;
    rectangles[0] = 40;
    rectangles[1] = 40;
    rectangles[2] = 20;
    rectangles[3] = 20;
    
    mask[0] = 5 | 16;
    values[0] = n1;
    values[1] = 0;
    
    mask[0] = 2 | 16;
    values[0] = n2;
    values[1] = 0;
    
    mask[0] = 8 | 256;
    values[0] = n3;
    values[1] = 4 | 1;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            mask[0] = 5 | 16;
            values[0] = n4;
            values[1] = 0;
        } else if (i == 1) {
            mask[0] = 2 | 16;
            values[0] = n5;
            values[1] = 0;
        } else if (i == 2) {
            mask[0] = 8 | 256;
            values[0] = n6;
            values[1] = 4 | 1;
        } else if (i == 3) {
            mask[0] = 5 | 16;
            values[0] = n7;
            values[1] = 0;
        } else {
            mask[0] = 2 | 16;
            values[0] = n8;
            values[1] = 0;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            mask[0] = 5 | 16;
            values[0] = n9;
            values[1] = 0;
        } else if (i == 1) {
            mask[0] = 2 | 16;
            values[0] = n10;
            values[1] = 0;
        }
    }
    
    return;
}
