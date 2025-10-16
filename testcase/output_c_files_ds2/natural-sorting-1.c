void natural_sort(int strings_len, int flags) {
    int i;
    int j;
    int k;
    int kw_s[5];
    int kw_w_s[5][5];
    int kw_w_n[5];
    int kw_w_alloc[5];
    int test[5][5] = {{0,0,0,0,0}, {1,0,0,0,0}, {9,9,0,0,0}, {1,0,0,0,0}, {0,0,0,0,0}};
    int str[5][5];
    int tbl_accent[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
    int tbl_ligature[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
    int tbl_article[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            str[i][j] = test[i][j];
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        kw_s[i] = 0;
        kw_w_n[i] = 0;
        kw_w_alloc[i] = 1;
        for (j = 0; j < 5; j = j + 1) {
            kw_w_s[i][j] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            kw_w_s[i][j] = str[i][j];
            kw_w_n[i] = kw_w_n[i] + 1;
            if (kw_w_n[i] >= kw_w_alloc[i]) {
                kw_w_alloc[i] = kw_w_alloc[i] * 2;
            }
        }
        
        for (k = 0; k < 5; k = k + 1) {
            if (flags & (1 << k)) {
                int c;
                int gotspace;
                int n;
                int len;
                int found;
                
                if (k == 0) {
                    gotspace = 0;
                    for (j = 0; j < 5; j = j + 1) {
                        c = kw_w_s[i][j];
                        if (c != 32) {
                            if (gotspace && kw_w_n[i] > 0) {
                                kw_w_s[i][kw_w_n[i]] = 32;
                                kw_w_n[i] = kw_w_n[i] + 1;
                            }
                            kw_w_s[i][kw_w_n[i]] = c;
                            kw_w_n[i] = kw_w_n[i] + 1;
                            gotspace = 0;
                        } else {
                            gotspace = 1;
                        }
                    }
                } else if (k == 1) {
                    for (j = 0; j < 5; j = j + 1) {
                        c = kw_w_s[i][j];
                        if (c >= 65 && c <= 90) {
                            c = c + 32;
                        }
                        kw_w_s[i][j] = c;
                    }
                } else if (k == 2 || k == 3) {
                    len = 5;
                    found = 0;
                    for (j = 0; j < 5; j = j + 1) {
                        c = kw_w_s[i][j];
                        for (n = 0; n < len; n = n + 2) {
                            if (c == (k == 2 ? tbl_accent[n][0] : tbl_ligature[n][0])) {
                                for (int m = 0; (k == 2 ? tbl_accent[n+1][m] : tbl_ligature[n+1][m]) != 0; m = m + 1) {
                                    kw_w_s[i][kw_w_n[i]] = (k == 2 ? tbl_accent[n+1][m] : tbl_ligature[n+1][m]);
                                    kw_w_n[i] = kw_w_n[i] + 1;
                                }
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            kw_w_s[i][kw_w_n[i]] = c;
                            kw_w_n[i] = kw_w_n[i] + 1;
                        }
                    }
                } else if (k == 4) {
                    int c0 = 0;
                    for (j = 0; j < 5; j = j + 1) {
                        c = kw_w_s[i][j];
                        if (!c0 || ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) && !((c0 >= 48 && c0 <= 57) || (c0 >= 65 && c0 <= 90) || (c0 >= 97 && c0 <= 122))) {
                            for (n = 4; n >= 0; n = n - 1) {
                                int match = 1;
                                for (int m = 0; tbl_article[n][m] != 0; m = m + 1) {
                                    if (kw_w_s[i][j + m] != tbl_article[n][m]) {
                                        match = 0;
                                        break;
                                    }
                                }
                                if (match) {
                                    j = j + 3;
                                    break;
                                }
                            }
                            if (n < 0) {
                                kw_w_s[i][kw_w_n[i]] = c;
                                kw_w_n[i] = kw_w_n[i] + 1;
                            }
                        } else {
                            kw_w_s[i][kw_w_n[i]] = c;
                            kw_w_n[i] = kw_w_n[i] + 1;
                        }
                        c0 = c;
                    }
                }
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            int cmp = 0;
            if (flags & 32) {
                int pa = 0;
                int pb = 0;
                while (kw_w_s[i][pa] != 0 && kw_w_s[j][pb] != 0) {
                    if (kw_w_s[i][pa] >= 48 && kw_w_s[i][pa] <= 57 && kw_w_s[j][pb] >= 48 && kw_w_s[j][pb] <= 57) {
                        int sa = 0;
                        int sb = 0;
                        int ea = 0;
                        int eb = 0;
                        while (kw_w_s[i][pa + sa] == 48) {
                            sa = sa + 1;
                        }
                        while (kw_w_s[j][pb + sb] == 48) {
                            sb = sb + 1;
                        }
                        ea = sa;
                        eb = sb;
                        while (kw_w_s[i][pa + ea] >= 48 && kw_w_s[i][pa + ea] <= 57) {
                            ea = ea + 1;
                        }
                        while (kw_w_s[j][pb + eb] >= 48 && kw_w_s[j][pb + eb] <= 57) {
                            eb = eb + 1;
                        }
                        if (eb - sb > ea - sa) {
                            cmp = -1;
                            break;
                        }
                        if (eb - sb < ea - sa) {
                            cmp = 1;
                            break;
                        }
                        while (sb < eb) {
                            if (kw_w_s[i][pa + sa] > kw_w_s[j][pb + sb]) {
                                cmp = 1;
                                break;
                            }
                            if (kw_w_s[i][pa + sa] < kw_w_s[j][pb + sb]) {
                                cmp = -1;
                                break;
                            }
                            sa = sa + 1;
                            sb = sb + 1;
                        }
                        pa = pa + ea;
                        pb = pb + eb;
                    } else if (kw_w_s[i][pa] >= 48 && kw_w_s[i][pa] <= 57) {
                        cmp = 1;
                        break;
                    } else if (kw_w_s[j][pb] >= 48 && kw_w_s[j][pb] <= 57) {
                        cmp = -1;
                        break;
                    } else {
                        if (kw_w_s[i][pa] > kw_w_s[j][pb]) {
                            cmp = 1;
                            break;
                        }
                        if (kw_w_s[i][pa] < kw_w_s[j][pb]) {
                            cmp = -1;
                            break;
                        }
                        pa = pa + 1;
                        pb = pb + 1;
                    }
                }
                if (cmp == 0) {
                    if (kw_w_s[i][pa] != 0 && kw_w_s[j][pb] == 0) {
                        cmp = 1;
                    } else if (kw_w_s[i][pa] == 0 && kw_w_s[j][pb] != 0) {
                        cmp = -1;
                    }
                }
            } else {
                int k = 0;
                while (kw_w_s[i][k] != 0 && kw_w_s[j][k] != 0) {
                    if (kw_w_s[i][k] > kw_w_s[j][k]) {
                        cmp = 1;
                        break;
                    }
                    if (kw_w_s[i][k] < kw_w_s[j][k]) {
                        cmp = -1;
                        break;
                    }
                    k = k + 1;
                }
                if (cmp == 0) {
                    if (kw_w_s[i][k] != 0 && kw_w_s[j][k] == 0) {
                        cmp = 1;
                    } else if (kw_w_s[i][k] == 0 && kw_w_s[j][k] != 0) {
                        cmp = -1;
                    }
                }
            }
            if (cmp > 0) {
                for (k = 0; k < 5; k = k + 1) {
                    int tmp = kw_w_s[i][k];
                    kw_w_s[i][k] = kw_w_s[j][k];
                    kw_w_s[j][k] = tmp;
                }
                int tmp = kw_w_n[i];
                kw_w_n[i] = kw_w_n[j];
                kw_w_n[j] = tmp;
                tmp = kw_w_alloc[i];
                kw_w_alloc[i] = kw_w_alloc[j];
                kw_w_alloc[j] = tmp;
                tmp = kw_s[i];
                kw_s[i] = kw_s[j];
                kw_s[j] = tmp;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            str[i][j] = kw_w_s[i][j];
        }
    }
    
    return;
}
