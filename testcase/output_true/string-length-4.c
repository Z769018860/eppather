int func(int n1, int n2) {
    int s[5] = {12303, 12399, 12424, 12354, 0};
    int length[5];
    int i;
    
    length[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (s[i] != 0) {
            length[0] = length[0] + 1;
        } else {
            break;
        }
    }
    
    return;
}
