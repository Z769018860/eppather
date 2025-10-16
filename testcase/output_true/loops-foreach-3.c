int func(int n1, int n2) {
    int a1[5] = {1, 1, 2, 3, 5};
    int a2[5] = {3, 1, 4, 1, 5};
    int* p1;
    int* p2;
    
    for (p1 = a1; p1 < (a1 + 5); p1 = p1 + 1) {
        int temp1 = *p1;
    }
    
    for (p2 = a2; p2 < (a2 + 5); p2 = p2 + 1) {
        int temp2 = *p2;
    }
    
    return;
}
