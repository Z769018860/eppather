void func(int MAXROW, int MAXCOL) {
    int colour[5];
    int i[5];
    int j[5];
    int n1 = 8;
    int n2;
    int n3;
    
    colour[0] = 0;
    for (colour[0] = 0; colour[0] < n1; colour[0] = colour[0] + 1) {
        for (j[0] = 0; j[0] < MAXROW; j[0] = j[0] + 1) {
            n2 = MAXCOL / n1;
            for (i[0] = 0; i[0] < n2; i[0] = i[0] + 1) {
            }
            n3 = 1 + colour[0] * MAXCOL / n1;
        }
    }
    return;
}
