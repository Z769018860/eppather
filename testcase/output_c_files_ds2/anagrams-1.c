void buildAnagrams(int buffer_size, int ht_size, int max_pc, int num_words, int hix, int hash, int mash, int t, int swaps, int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s, int u, int v, int w, int x, int y, int z) {
    char buffer[40];
    char bufr2[40];
    char hkey[40];
    int cxmap[96] = {6, 31, 77, 12, 92, 40, 93, 14, 9, 51, 49, 86, 82, 25, 41, 83, 50, 72, 53, 85, 94, 20, 39, 36, 2, 62, 24, 74, 63, 76, 69, 48, 8, 44, 26, 3, 11, 13, 79, 7, 32, 29, 81, 59, 17, 88, 0, 73, 21, 45, 65, 23, 95, 57, 22, 66, 55, 34, 28, 15, 67, 91, 70, 75, 10, 38, 46, 64, 18, 33, 60, 54, 56, 30, 1, 27, 5, 78, 68, 61, 4, 16, 90, 42, 35, 52, 37, 47, 43, 80, 58, 84, 71, 89, 19, 87};
    int hash_table[8192];
    int most_perms[5];
    int he[5];
    int hep[5];
    int we[5];
    int max_pc_local = 2;
    int num_words_local = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        buffer[i] = 0;
        bufr2[i] = 0;
        hkey[i] = 0;
        hash_table[i] = 0;
        most_perms[i] = 0;
        he[i] = 0;
        hep[i] = 0;
        we[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            hkey[j] = buffer[j];
            if (hkey[j] == '\n') {
                hkey[j] = 0;
            }
        }
        
        for (j = 0; j < 5; j = j + 1) {
            bufr2[j] = hkey[j];
        }
        
        swaps = 1;
        while (swaps) {
            swaps = 0;
            for (k = 0; k < 5; k = k + 1) {
                for (l = 4; l > k; l = l - 1) {
                    if (bufr2[l] > bufr2[k]) {
                        t = bufr2[l];
                        bufr2[l] = bufr2[k];
                        bufr2[k] = t;
                        swaps = 1;
                    }
                }
            }
            for (k = 0; k < 4; k = k + 1) {
                if (bufr2[k + 1] > bufr2[k]) {
                    t = bufr2[k + 1];
                    bufr2[k + 1] = bufr2[k];
                    bufr2[k] = t;
                    swaps = 1;
                }
            }
        }
        
        hash = 33501551;
        for (k = 0; k < 5; k = k + 1) {
            if (hkey[k] == 0) {
                break;
            }
            mash = cxmap[hkey[k] % 96];
            hash = (hash >> 4) ^ 96874844 ^ ((hash << 1) + (mash << 5));
            hash = hash & 805306367;
        }
        hix = hash % ht_size;
        
        he[0] = hash_table[hix];
        hep[0] = hash_table[hix];
        while (he[0] && he[0] != hkey[0]) {
            hep[0] = he[0];
            he[0] = he[0] + 1;
        }
        
        if (!he[0]) {
            he[0] = 1;
            he[1] = 0;
            he[2] = hkey[0];
            he[3] = 0;
            he[4] = 0;
            hep[0] = he[0];
        }
        
        we[0] = 1;
        we[1] = buffer[0];
        we[2] = he[4];
        he[4] = we[0];
        he[3] = he[3] + 1;
        
        if (max_pc_local < he[3]) {
            max_pc_local = he[3];
            most_perms[0] = he[0];
            he[4] = 0;
        } else if (max_pc_local == he[3]) {
            he[4] = most_perms[0];
            most_perms[0] = he[0];
        }
        
        num_words_local = num_words_local + 1;
    }
    return;
}
