void findPythagoreanTriples() {
    int n = 20;
    int triples[100][3];
    int count = 0;
    
    for (int x = 1; x <= n; x = x + 1) {
        for (int y = x; y <= n; y = y + 1) {
            for (int z = y; z <= n; z = z + 1) {
                if (x * x + y * y == z * z) {
                    triples[count][0] = x;
                    triples[count][1] = y;
                    triples[count][2] = z;
                    count = count + 1;
                }
            }
        }
    }
    
    return;
}
