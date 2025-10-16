int dao(int cmd, int in_db[5][100], int sortby) {
    int pdb[100][100];
    int rec[100];
    int hd[100];
    int i;
    int ret;
    int buf[100];
    
    if (cmd == 0) {
        for (i = 0; i < 25; i = i + 1) {
            in_db[0][i] = in_db[0][i];
        }
        for (i = 0; i < 25; i = i + 1) {
            in_db[1][i] = in_db[1][i];
        }
        for (i = 0; i < 25; i = i + 1) {
            in_db[2][i] = in_db[2][i];
        }
        for (i = 0; i < 100; i = i + 1) {
            in_db[3][i] = in_db[3][i];
        }
    }
    
    if (cmd == 1) {
        for (i = 0; i < 100; i = i + 1) {
            if (in_db[i][0] != 0) {
                for (int j = 0; j < 25; j = j + 1) {
                    buf[j] = in_db[i][j];
                }
                for (int j = 0; j < 25; j = j + 1) {
                    buf[j + 25] = in_db[i][j + 25];
                }
                for (int j = 0; j < 100; j = j + 1) {
                    buf[j + 50] = in_db[i][j + 50];
                }
            }
        }
    }
    
    if (cmd == 2) {
        for (i = 0; i < 100; i = i + 1) {
            if (in_db[i][0] != 0) {
                for (int j = 0; j < 25; j = j + 1) {
                    rec[j] = in_db[i][j];
                }
                for (int j = 0; j < 25; j = j + 1) {
                    rec[j + 25] = in_db[i][j + 25];
                }
                for (int j = 0; j < 100; j = j + 1) {
                    rec[j + 50] = in_db[i][j + 50];
                }
                for (int j = 0; j < 100; j = j + 1) {
                    hd[j] = rec[j];
                }
            }
        }
    }
    
    if (cmd == 3) {
        for (i = 0; i < 100; i = i + 1) {
            if (in_db[i][0] != 0) {
                for (int j = 0; j < 100; j = j + 1) {
                    pdb[i][j] = in_db[i][j];
                }
            }
        }
        for (i = 0; i < 100; i = i + 1) {
            for (int j = 0; j < 100; j = j + 1) {
                if (pdb[i][j] > pdb[i + 1][j] && sortby == 1) {
                    int temp[100];
                    for (int k = 0; k < 100; k = k + 1) {
                        temp[k] = pdb[i][k];
                        pdb[i][k] = pdb[i + 1][k];
                        pdb[i + 1][k] = temp[k];
                    }
                }
            }
        }
        for (i = 0; i < 100; i = i + 1) {
            if (pdb[i][0] != 0) {
                for (int j = 0; j < 100; j = j + 1) {
                    rec[j] = pdb[i][j];
                }
            }
        }
    }
    
    if (cmd == 4) {
        for (i = 0; i < 100; i = i + 1) {
            if (in_db[i][0] != 0) {
                for (int j = 0; j < 100; j = j + 1) {
                    in_db[i][j] = 0;
                }
            }
        }
    }
    
    return;
}
