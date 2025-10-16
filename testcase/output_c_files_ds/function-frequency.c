void addToList(int list_name[100][2], int list_marked[100], char list_names[100][50], char toAdd_name[50], int numElements, int allocatedSize) {
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    int i;
    int j;
    int found_keyword;
    
    found_keyword = 0;
    for (i = 0; i < 32; i = i + 1) {
        for (j = 0; keywords[i][j] != '\0' && toAdd_name[j] != '\0'; j = j + 1) {
            if (keywords[i][j] != toAdd_name[j]) {
                break;
            }
        }
        if (keywords[i][j] == '\0' && toAdd_name[j] == '\0') {
            found_keyword = 1;
            break;
        }
    }
    if (found_keyword) {
        return;
    }
    
    if (numElements == 0) {
        for (i = 0; toAdd_name[i] != '\0'; i = i + 1) {
            list_names[0][i] = toAdd_name[i];
        }
        list_names[0][i] = '\0';
        list_name[0][1] = 1;
        list_marked[0] = 0;
        numElements = 1;
    } else {
        int found;
        found = 0;
        for (i = 0; i < numElements; i = i + 1) {
            for (j = 0; list_names[i][j] != '\0' && toAdd_name[j] != '\0'; j = j + 1) {
                if (list_names[i][j] != toAdd_name[j]) {
                    break;
                }
            }
            if (list_names[i][j] == '\0' && toAdd_name[j] == '\0') {
                found = 1;
                list_name[i][1] = list_name[i][1] + 1;
                break;
            }
        }
        if (found == 0) {
            for (i = 0; toAdd_name[i] != '\0'; i = i + 1) {
                list_names[numElements][i] = toAdd_name[i];
            }
            list_names[numElements][i] = '\0';
            list_name[numElements][1] = 1;
            list_marked[numElements] = 0;
            numElements = numElements + 1;
        }
    }
    return;
}
