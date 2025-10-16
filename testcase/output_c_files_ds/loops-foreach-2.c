void rewritten_function() {
    char s1[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\0'};
    char s2[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    char* p1;
    char* p2;
    
    for (p1 = s1; (*p1) != '\0'; p1 = p1 + 1) {
        char temp1 = *p1;
    }
    
    for (p2 = s2; (*p2) != '\0'; p2 = p2 + 1) {
        char temp2 = *p2;
    }
    
    return;
}
