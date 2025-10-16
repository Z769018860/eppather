void iter(int v[15], int diff[15]) {
    int sum;
    int i;
    int j;
    int e;
    int temp;
    
    v[0] = 151;
    v[5] = 40;
    v[12] = 11;
    v[14] = 4;
    
    for (i = 1; i < 5; i = i + 1) {
        for (j = 0; j <= i; j = j + 1) {
            temp = i * (i + 1) / 2 + j;
            diff[temp] = 0;
            if (j < i) {
                diff[temp] = diff[temp] + v[(i - 1) * i / 2 + j] - v[i * (i + 1) / 2 + j + 1] - v[temp];
            }
            if (j > 0) {
                diff[temp] = diff[temp] + v[(i - 1) * i / 2 + j - 1] - v[i * (i + 1) / 2 + j - 1] - v[temp];
            }
        }
    }
    
    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < i; j = j + 1) {
            diff[i * (i + 1) / 2 + j] = diff[i * (i + 1) / 2 + j] + v[(i + 1) * (i + 2) / 2 + j] + v[(i + 1) * (i + 2) / 2 + j + 1] - v[i * (i + 1) / 2 + j];
        }
    }
    
    diff[11] = diff[11] + v[10] + v[14] - v[11];
    
    sum = 0;
    for (i = 0; i < 15; i = i + 1) {
        e = diff[i];
        if (e < 0) {
            temp = -1;
        } else {
            if (e > 0) {
                temp = 1;
            } else {
                temp = 0;
            }
        }
        if (temp != 0) {
            sum = sum + 1;
        }
        
        if (e >= 4 || e <= -4) {
            v[i] = v[i] + e / 5;
        } else {
            if (e < 0) {
                v[i] = v[i] - 1;
            } else {
                if (e > 0) {
                    v[i] = v[i] + 1;
                }
            }
        }
    }
    
    return;
}
