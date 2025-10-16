void stable_marriage(int men_prefers[5][5], int women_prefers[5][5], int men_partner[5], int women_partner[5]) {
    int bachelors[5];
    int bachelors_size = 5;
    int man_index[5] = {0};
    int woman_index[5] = {0};
    
    for (int i = 0; i < 5; i = i + 1) {
        bachelors[i] = i;
        men_partner[i] = -1;
        women_partner[i] = -1;
    }
    
    while (bachelors_size > 0) {
        int man = bachelors[bachelors_size - 1];
        int woman = men_prefers[man][man_index[man]];
        
        if (women_partner[woman] == -1) {
            women_partner[woman] = man;
            men_partner[man] = woman;
            bachelors_size = bachelors_size - 1;
        } else {
            int current_man = women_partner[woman];
            int prefer_current = 0;
            int prefer_new = 0;
            
            for (int i = 0; i < 5; i = i + 1) {
                if (women_prefers[woman][i] == current_man) {
                    prefer_current = 1;
                    break;
                }
                if (women_prefers[woman][i] == man) {
                    prefer_new = 1;
                    break;
                }
            }
            
            if (prefer_new) {
                women_partner[woman] = man;
                men_partner[man] = woman;
                men_partner[current_man] = -1;
                bachelors[bachelors_size - 1] = current_man;
                man_index[current_man] = man_index[current_man] + 1;
            } else {
                man_index[man] = man_index[man] + 1;
            }
        }
    }
    return;
}
