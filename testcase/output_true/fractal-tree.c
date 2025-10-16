void draw_tree(int surface_w, int surface_h, int surface_pitch, int surface_format, int offsetx, int offsety, int directionx, int directiony, int size, int rotation, int depth) {
    int n1 = 5;
    int n2 = 14;
    int n3 = 50;
    int n4 = 800;
    int n5 = 31415926535;
    int n6 = 8;
    int n7 = 255;
    
    int x1[5];
    int x2[5];
    int x3[5];
    int x4[5];
    int x5[5];
    int x6[5];
    int x7[5];
    int x8[5];
    int x9[5];
    int x10[5];
    
    x1[0] = offsetx;
    x2[0] = offsety;
    x3[0] = directionx;
    x4[0] = directiony;
    x5[0] = size;
    x6[0] = rotation;
    x7[0] = depth;
    
    if (x7[0] > 0) {
        for (int i = 0; i < n1; i = i + 1) {
            x8[0] = x3[0];
            x9[0] = x4[0];
            x10[0] = x6[0];
            
            x3[0] = x8[0] * 91630 / 100000 + x9[0] * 39999 / 100000;
            x4[0] = x8[0] * -39999 / 100000 + x9[0] * 91630 / 100000;
            x5[0] = x5[0] * 32767 / 65535 / n1 + x5[0] * (n1 - 1) / n1;
            x6[0] = x10[0] * 75 / 100;
            x7[0] = x7[0] - 1;
            
            draw_tree(surface_w, surface_h, surface_pitch, surface_format, x1[0] + x8[0] * x5[0], x2[0] + x9[0] * x5[0], x3[0], x4[0], x5[0], x6[0], x7[0]);
            
            x3[0] = x8[0] * 91630 / 100000 + x9[0] * -39999 / 100000;
            x4[0] = x8[0] * 39999 / 100000 + x9[0] * 91630 / 100000;
            x5[0] = x5[0] * 32767 / 65535 / n1 + x5[0] * (n1 - 1) / n1;
            x6[0] = x10[0] * 75 / 100;
            x7[0] = x7[0] - 1;
            
            draw_tree(surface_w, surface_h, surface_pitch, surface_format, x1[0] + x8[0] * x5[0], x2[0] + x9[0] * x5[0], x3[0], x4[0], x5[0], x6[0], x7[0]);
        }
    }
    return;
}
