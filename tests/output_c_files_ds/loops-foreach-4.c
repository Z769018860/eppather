int rewritten_function() {
    char c1[10] = {'c', 'o', 'l', 'l', 'e', 'c', 't', 'i', 'o', 'n'};
    int c2[6] = {3, 1, 4, 1, 5, 9};
    double c3[4] = {1.2, 3.4, 5.6, 7.8};
    char* p1;
    int* p2;
    double* p3;
    int i;
    
    for (p1 = c1; p1 < (c1 + 10); p1 = p1 + 1) {
    }
    
    for (p2 = c2; p2 < (c2 + 6); p2 = p2 + 1) {
    }
    
    for (p3 = c3; p3 < (c3 + 4); p3 = p3 + 1) {
    }
    
    return;
}
