const char* menu_select(const char* const* items, const char* prompt) {
    int buf[5];
    int i;
    int choice;
    int choice_max;
    int n1;
    int n2;
    int n3;
    
    if (items == 0) {
        return 0;
    }
    
    for (n1 = 0; n1 < 5; n1 = n1 + 1) {
        buf[n1] = 0;
    }
    
    for (i = 0; items[i] != 0; i = i + 1) {
    }
    choice_max = i;
    
    for (n2 = 0; n2 < 5; n2 = n2 + 1) {
        if (n2 < choice_max) {
        }
    }
    
    for (n3 = 0; n3 < 5; n3 = n3 + 1) {
        if (prompt != 0) {
        } else {
        }
    }
    
    choice = 1;
    if (1 > choice || choice > choice_max) {
    } else {
        return items[choice - 1];
    }
    
    return 0;
}
