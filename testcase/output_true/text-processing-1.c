int mungeLine(int line[5], int lno[5], int fout[5]) {
    int date[40];
    int tkn[40];
    int dHrs[5];
    int flag[5];
    int hrs2[5];
    int hrs[5];
    int hrsSum[5];
    int hrsCnt[5];
    int avg[5];
    int n[5];
    int badHrs[5];
    int maxBadHrs[5];
    int bhEndDate[40];
    int hrsTot[5];
    int rdgsTot[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        tkn[i] = line[i];
    }
    if (tkn[0]) {
        n[0] = 2;
        for (i = 0; i < 5; i = i + 1) {
            date[i] = tkn[i];
        }
        hrs2[0] = tkn[5];
        if (n[0] < 2) {
            return 0;
        }
        hrsSum[0] = 0;
        hrsCnt[0] = 0;
        for (i = 0; i < 5; i = i + 1) {
            tkn[i] = line[i + 6];
        }
        if (tkn[0]) {
            n[0] = 2;
            dHrs[0] = tkn[0];
            flag[0] = tkn[1];
            hrs[0] = tkn[2];
            if (n[0] >= 2) {
                if (flag[0] > 0) {
                    hrsSum[0] = hrsSum[0] + hrs2[0] + dHrs[0] / 1000;
                    hrsCnt[0] = hrsCnt[0] + 1;
                    if (maxBadHrs[0] < badHrs[0]) {
                        maxBadHrs[0] = badHrs[0];
                        for (i = 0; i < 5; i = i + 1) {
                            bhEndDate[i] = date[i];
                        }
                    }
                    badHrs[0] = 0;
                } else {
                    badHrs[0] = badHrs[0] + 1;
                }
                hrs2[0] = hrs[0];
            } else {
                return 0;
            }
        }
        if (hrsCnt[0] > 0) {
            avg[0] = hrsSum[0] / hrsCnt[0];
        } else {
            avg[0] = 0;
        }
        hrsTot[0] = hrsTot[0] + hrsSum[0];
        rdgsTot[0] = rdgsTot[0] + hrsCnt[0];
    }
    return 1;
}
