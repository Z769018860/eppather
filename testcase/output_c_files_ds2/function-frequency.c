void addToList(int list_name[5][5], int list_timesCalled[5], int list_marked[5], int toAdd_name[5], int numElements, int allocatedSize) {
    int keywords[32][5] = {{97,117,116,111,0}, {98,114,101,97,107}, {99,97,115,101,0}, {99,104,97,114,0}, {99,111,110,115,116}, 
                          {99,111,110,116,105}, {100,101,102,97,117}, {100,111,0,0,0}, {100,111,117,98,108}, 
                          {101,108,115,101,0}, {101,110,117,109,0}, {101,120,116,101,114}, {102,108,111,97,116}, {102,111,114,0,0}, 
                          {103,111,116,111,0}, {105,102,0,0,0}, {105,110,116,0,0}, {108,111,110,103,0}, {114,101,103,105,115}, 
                          {114,101,116,117,114}, {115,104,111,114,116}, {115,105,103,110,101}, {115,105,122,101,111}, 
                          {115,116,97,116,105}, {115,116,114,117,99}, {115,119,105,116,99}, {116,121,112,101,100}, 
                          {117,110,105,111,110}, {117,110,115,105,103}, {118,111,105,100,0}, {118,111,108,97,116}, 
                          {119,104,105,108,101}};
    int i;
    int j;
    int match;
    for (i = 0; i < 5; i = i + 1) {
        match = 1;
        for (j = 0; j < 5; j = j + 1) {
            if (keywords[i][j] != toAdd_name[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return;
        }
    }
    if (numElements == 0) {
        allocatedSize = 10;
        for (i = 0; i < 5; i = i + 1) {
            list_name[0][i] = toAdd_name[i];
        }
        list_timesCalled[0] = 1;
        list_marked[0] = 0;
        numElements = 1;
    } else {
        int found = 0;
        for (i = 0; i < numElements; i = i + 1) {
            match = 1;
            for (j = 0; j < 5; j = j + 1) {
                if (list_name[i][j] != toAdd_name[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                found = 1;
                list_timesCalled[i] = list_timesCalled[i] + 1;
                break;
            }
        }
        if (!found) {
            for (i = 0; i < 5; i = i + 1) {
                list_name[numElements][i] = toAdd_name[i];
            }
            list_timesCalled[numElements] = 1;
            list_marked[numElements] = 0;
            numElements = numElements + 1;
        }
    }
    return;
}
