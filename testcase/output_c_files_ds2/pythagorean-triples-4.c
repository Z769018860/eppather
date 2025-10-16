void countTriples(int max_perimeter, int* triples, int* primitives) {
    int a;
    int b;
    int c;
    int perimeter;
    int m;
    int n;
    int k;
    int limit;
    int a2;
    int b2;
    int c2;
    int gcd_temp;
    int temp;
    
    *triples = 0;
    *primitives = 0;
    limit = max_perimeter;
    
    for (m = 2; m < 5; m = m + 1) {
        for (n = 1; n < m; n = n + 1) {
            a = m * m - n * n;
            b = 2 * m * n;
            c = m * m + n * n;
            perimeter = a + b + c;
            
            if (perimeter > limit) {
                continue;
            }
            
            gcd_temp = m;
            temp = n;
            while (temp != 0) {
                int remainder = gcd_temp % temp;
                gcd_temp = temp;
                temp = remainder;
            }
            
            if (gcd_temp == 1) {
                *primitives = *primitives + 1;
            }
            
            for (k = 1; k < 5; k = k + 1) {
                a2 = k * a;
                b2 = k * b;
                c2 = k * c;
                perimeter = a2 + b2 + c2;
                
                if (perimeter > limit) {
                    break;
                }
                
                *triples = *triples + 1;
            }
        }
    }
    return;
}
