int func() {
    int a1[6] = {1, 1, 2, 3, 5, 8};
    int a2[6] = {3, 1, 4, 1, 5, 9};
    int* p1;
    int* p2;
    
    for (p1 = a1; p1 < (a1 + 6); p1 = p1 + 1) {
    }
    
    for (p2 = a2; p2 < (a2 + 6); p2 = p2 + 1) {
    }
    
    return;
}
