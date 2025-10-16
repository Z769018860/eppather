int a2D_Array[3][5];
int my2Dfloats[2][3] = {
   1, 2, 0,
   5, 1, 3 };

void func(int float_rows) {
    int i;
    int j;
    for (i = 0; i < 3; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            a2D_Array[i][j] = 0;
        }
    }
    for (i = 0; i < float_rows; i = i + 1) {
        for (j = 0; j < 3; j = j + 1) {
            my2Dfloats[i][j] = 0;
        }
    }
    return;
}
