int func(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20, int n21, int n22, int n23, int n24, int n25, int n26, int n27, int n28) {
    int target[28] = {77,69,84,72,73,78,75,83,32,73,84,32,73,83,32,76,73,75,69,32,65,32,87,69,65,83,69,76};
    int tbl[27] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,32};
    int specimen[30][28];
    int i;
    int j;
    int k;
    int best_i;
    int unfit;
    int best;
    int iters;
    int r;
    int rand_max;
    int sum;
    int choice;
    int mutate;
    int copies;
    
    choice = 27;
    mutate = 15;
    copies = 30;
    iters = 0;
    
    for (i = 0; i < 28; i = i + 1) {
        rand_max = 2147483647 - (2147483647 % choice);
        while (1) {
            r = 12345;
            if (r < rand_max) {
                break;
            }
        }
        specimen[0][i] = tbl[r / (rand_max / choice)];
    }
    
    do {
        for (i = 1; i < copies; i = i + 1) {
            for (j = 0; j < 28; j = j + 1) {
                rand_max = 2147483647 - (2147483647 % mutate);
                while (1) {
                    r = 12345;
                    if (r < rand_max) {
                        break;
                    }
                }
                if (r / (rand_max / mutate)) {
                    specimen[i][j] = specimen[0][j];
                } else {
                    rand_max = 2147483647 - (2147483647 % choice);
                    while (1) {
                        r = 12345;
                        if (r < rand_max) {
                            break;
                        }
                    }
                    specimen[i][j] = tbl[r / (rand_max / choice)];
                }
            }
        }
        
        best_i = 0;
        for (i = 0; i < copies; i = i + 1) {
            sum = 0;
            for (j = 0; j < 28; j = j + 1) {
                if (specimen[i][j] != target[j]) {
                    sum = sum + 1;
                }
            }
            if (i == 0 || sum < best) {
                best = sum;
                best_i = i;
            }
        }
        
        if (best_i != 0) {
            for (k = 0; k < 28; k = k + 1) {
                specimen[0][k] = specimen[best_i][k];
            }
        }
        iters = iters + 1;
    } while (best != 0);
    
    return;
}
