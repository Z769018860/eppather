void stable_marriage(int men_id[5], int men_partner[5], int men_prefers[5][5], int men_index[5], int women_id[5], int women_partner[5], int women_prefers[5][5], int women_index[5], int size) {
    int bachelors[5];
    int bachelors_size;
    int i;
    int j;
    int k;
    int man;
    int woman;
    int current_partner;
    int found;
    
    for (i = 0; i < size; i = i + 1) {
        bachelors[i] = i;
    }
    bachelors_size = size;
    
    while (bachelors_size > 0) {
        man = bachelors[bachelors_size - 1];
        woman = men_prefers[man][men_index[man]];
        
        if (women_partner[woman] == -1) {
            women_partner[woman] = man;
            men_partner[man] = woman;
            bachelors_size = bachelors_size - 1;
        } else {
            current_partner = women_partner[woman];
            found = 0;
            
            for (k = 0; k < size; k = k + 1) {
                if (women_prefers[woman][k] == current_partner) {
                    found = 1;
                    break;
                } else if (women_prefers[woman][k] == man) {
                    found = 0;
                    break;
                }
            }
            
            if (found == 0) {
                men_index[current_partner] = men_index[current_partner] + 1;
                bachelors[bachelors_size - 1] = current_partner;
                women_partner[woman] = man;
                men_partner[man] = woman;
            } else {
                men_index[man] = men_index[man] + 1;
            }
        }
    }
    
    return;
}
