void findPythagoreanTriples(int n) {
    int x[5];
    int y[5];
    int z[5];
    int triples[5][3];
    int count = 0;
    
    for (x[0] = 1; x[0] <= 5; x[0] = x[0] + 1) {
        for (y[0] = x[0]; y[0] <= 5; y[0] = y[0] + 1) {
            for (z[0] = y[0]; z[0] <= 5; z[0] = z[0] + 1) {
                if (x[0] * x[0] + y[0] * y[0] == z[0] * z[0]) {
                    if (count < 5) {
                        triples[count][0] = x[0];
                        triples[count][1] = y[0];
                        triples[count][2] = z[0];
                        count = count + 1;
                    }
                }
            }
        }
    }
    return;
}
