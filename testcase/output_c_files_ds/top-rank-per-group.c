int top(int n) {
    char* ppl_name[13] = {"Tyler Bennett", "John Rappl", "George Woltman", "Adam Smith", "Claire Buckman", "David McClellan", "Rich Holcomb", "Nathan Adams", "Richard Potter", "David Motsinger", "Tim Sampair", "Kim Arlich", "Timothy Grove"};
    char* ppl_id[13] = {"E10297", "E21437", "E00127", "E63535", "E39876", "E04242", "E01234", "E41298", "E43128", "E27002", "E03033", "E10001", "E16398"};
    char* ppl_dept[13] = {"D101", "D050", "D101", "D202", "D202", "D101", "D202", "D050", "D101", "D202", "D101", "D190", "D190"};
    int ppl_sal[13] = {32000, 47000, 53500, 18000, 27800, 41500, 49500, 21900, 15900, 19250, 27000, 57000, 29900};
    int i;
    int j;
    int temp_sal;
    char* temp_name;
    char* temp_id;
    char* temp_dept;
    int rank;
    int count;
    
    for (i = 0; i < 13; i = i + 1) {
        for (j = i + 1; j < 13; j = j + 1) {
            if (ppl_dept[i][0] > ppl_dept[j][0] || (ppl_dept[i][0] == ppl_dept[j][0] && ppl_dept[i][1] > ppl_dept[j][1]) || (ppl_dept[i][0] == ppl_dept[j][0] && ppl_dept[i][1] == ppl_dept[j][1] && ppl_dept[i][2] > ppl_dept[j][2]) || (ppl_dept[i][0] == ppl_dept[j][0] && ppl_dept[i][1] == ppl_dept[j][1] && ppl_dept[i][2] == ppl_dept[j][2] && ppl_sal[i] < ppl_sal[j])) {
                temp_sal = ppl_sal[i];
                ppl_sal[i] = ppl_sal[j];
                ppl_sal[j] = temp_sal;
                temp_name = ppl_name[i];
                ppl_name[i] = ppl_name[j];
                ppl_name[j] = temp_name;
                temp_id = ppl_id[i];
                ppl_id[i] = ppl_id[j];
                ppl_id[j] = temp_id;
                temp_dept = ppl_dept[i];
                ppl_dept[i] = ppl_dept[j];
                ppl_dept[j] = temp_dept;
            }
        }
    }
    
    rank = 0;
    count = 0;
    for (i = 0; i < 13; i = i + 1) {
        if (i != 0 && (ppl_dept[i][0] != ppl_dept[i-1][0] || ppl_dept[i][1] != ppl_dept[i-1][1] || ppl_dept[i][2] != ppl_dept[i-1][2])) {
            rank = 0;
            count = count + 1;
        }
        if (rank < n) {
            rank = rank + 1;
            count = count + 1;
        }
    }
    return count;
}
