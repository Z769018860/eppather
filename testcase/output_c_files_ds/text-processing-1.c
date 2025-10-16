int mungeLine(char line[512], int lno) {
    char date[40];
    int dHrs;
    int flag;
    int hrs2;
    int hrs;
    double hrsSum;
    int hrsCnt;
    double avg;
    int i;
    int j;
    int k;
    int n;
    int found;
    char temp[40];
    int tempHrs;
    
    hrsCnt = 0;
    hrsSum = 0.0;
    found = 0;
    
    for (i = 0; i < 40; i = i + 1) {
        date[i] = 0;
    }
    
    for (i = 0; i < 512; i = i + 1) {
        if (line[i] == '.') {
            found = 1;
            break;
        }
    }
    
    if (found) {
        for (i = 0; i < 512; i = i + 1) {
            if (line[i] == ' ') {
                break;
            }
            date[i] = line[i];
        }
        
        for (j = i + 1; j < 512; j = j + 1) {
            if (line[j] == ' ' || line[j] == '.') {
                break;
            }
        }
        
        for (k = 0; k < 40; k = k + 1) {
            temp[k] = 0;
        }
        
        for (k = 0; k < (j - i - 1); k = k + 1) {
            temp[k] = line[i + 1 + k];
        }
        
        tempHrs = 0;
        for (k = 0; k < 40; k = k + 1) {
            if (temp[k] >= '0' && temp[k] <= '9') {
                tempHrs = tempHrs * 10 + (temp[k] - '0');
            } else {
                break;
            }
        }
        hrs2 = tempHrs;
        
        for (i = j; i < 512; i = i + 1) {
            if (line[i] == '.') {
                for (k = 0; k < 40; k = k + 1) {
                    temp[k] = 0;
                }
                
                n = 0;
                for (j = i + 1; j < 512; j = j + 1) {
                    if (line[j] == ' ' || line[j] == '.') {
                        n = n + 1;
                        if (n == 3) {
                            break;
                        }
                    }
                }
                
                for (k = 0; k < (j - i - 1); k = k + 1) {
                    temp[k] = line[i + 1 + k];
                }
                
                dHrs = 0;
                flag = 0;
                hrs = 0;
                n = 0;
                for (k = 0; k < 40; k = k + 1) {
                    if (temp[k] >= '0' && temp[k] <= '9') {
                        if (n == 0) {
                            dHrs = dHrs * 10 + (temp[k] - '0');
                        } else if (n == 1) {
                            flag = flag * 10 + (temp[k] - '0');
                        } else if (n == 2) {
                            hrs = hrs * 10 + (temp[k] - '0');
                        }
                    } else if (temp[k] == ' ') {
                        n = n + 1;
                    } else {
                        break;
                    }
                }
                
                if (n >= 1) {
                    if (flag > 0) {
                        hrsSum = hrsSum + 1.0 * hrs2 + 0.001 * dHrs;
                        hrsCnt = hrsCnt + 1;
                        if (maxBadHrs < badHrs) {
                            maxBadHrs = badHrs;
                            for (k = 0; k < 40; k = k + 1) {
                                bhEndDate[k] = date[k];
                            }
                        }
                        badHrs = 0;
                    } else {
                        badHrs = badHrs + 1;
                    }
                    hrs2 = hrs;
                }
            }
        }
        
        if (hrsCnt > 0) {
            avg = hrsSum / hrsCnt;
        } else {
            avg = 0.0;
        }
        
        hrsTot = hrsTot + hrsSum;
        rdgsTot = rdgsTot + hrsCnt;
    }
    return 1;
}
