void ranking(int list_score[5], char list_name[5][100], int len) {
    int i;
    int j;
    int count;
    int sum;
    int temp;
    int rank;
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            temp = i + 1;
        }
    }
    
    rank = 1;
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            if (i > 0) {
                if (list_score[i] < list_score[i - 1]) {
                    rank = i + 1;
                }
            }
        }
    }
    
    rank = 1;
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            if (i > 0) {
                if (list_score[i] < list_score[i - 1]) {
                    rank = rank + 1;
                }
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < len - 1) {
            if (list_score[i] != list_score[i + 1]) {
                count = 1;
                for (j = i + 1; j < 5; j = j + 1) {
                    if (j < len - 1) {
                        if (list_score[j] == list_score[j + 1]) {
                            count = count + 1;
                        }
                    }
                }
                for (j = 0; j < 5; j = j + 1) {
                    if (j < count - 1) {
                        temp = i + count + 1;
                    }
                }
                i = i + (count - 1);
            }
        }
    }
    
    sum = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            if (i == len - 1) {
                temp = i + 1;
            }
            else {
                if (list_score[i] == list_score[i + 1]) {
                    sum = i;
                    count = 1;
                    for (j = i; j < 5; j = j + 1) {
                        if (j < len - 1) {
                            if (list_score[j] == list_score[j + 1]) {
                                sum = sum + (j + 1);
                                count = count + 1;
                            }
                        }
                    }
                    for (j = 0; j < 5; j = j + 1) {
                        if (j < count) {
                            temp = sum / count + 1;
                        }
                    }
                    i = i + (count - 1);
                }
            }
        }
    }
    return;
}
