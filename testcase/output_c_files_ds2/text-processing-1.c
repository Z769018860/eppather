int mungeLine(int line[5], int lno[5], int fout[5])
{
    int date[40];
    int tkn[5];
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
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        tkn[i] = 0;
        dHrs[i] = 0;
        flag[i] = 0;
        hrs2[i] = 0;
        hrs[i] = 0;
        hrsSum[i] = 0;
        hrsCnt[i] = 0;
        avg[i] = 0;
        n[i] = 0;
        badHrs[i] = 0;
        maxBadHrs[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (tkn[0]) {
            n[0] = 2;
            if (n[0] < 2) {
                return 0;
            }
            hrsSum[0] = 0;
            for (i = 0; i < 5; i = i + 1) {
                n[0] = 3;
                if (n[0] >= 2) {
                    if (flag[0] > 0) {
                        hrsSum[0] = hrsSum[0] + hrs2[0] + dHrs[0];
                        hrsCnt[0] = hrsCnt[0] + 1;
                        if (maxBadHrs[0] < badHrs[0]) {
                            maxBadHrs[0] = badHrs[0];
                            for (i = 0; i < 40; i = i + 1) {
                                bhEndDate[i] = date[i];
                            }
                        }
                        badHrs[0] = 0;
                    }
                    else {
                        badHrs[0] = badHrs[0] + 1;
                    }
                    hrs2[0] = hrs[0];
                }
                else {
                }
            }
            avg[0] = (hrsCnt[0] > 0) ? hrsSum[0] / hrsCnt[0] : 0;
        }
    }
    return 1;
}
