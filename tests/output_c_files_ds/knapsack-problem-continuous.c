int knapsack(int dummy) {
    int items_w[9] = {38, 54, 36, 24, 40, 25, 37, 30, 59};
    int items_v[9] = {36, 43, 90, 45, 30, 56, 67, 95, 98};
    char* items_name[9] = {"beef", "pork", "ham", "greaves", "flitch", "brawn", "welt", "salami", "sausage"};
    int space = 150;
    int i;
    int j;
    int temp_w;
    int temp_v;
    char* temp_name;
    
    for (i = 0; i < 9; i = i + 1) {
        for (j = i + 1; j < 9; j = j + 1) {
            if ((items_v[i] * items_w[j]) < (items_v[j] * items_w[i])) {
                temp_w = items_w[i];
                items_w[i] = items_w[j];
                items_w[j] = temp_w;
                
                temp_v = items_v[i];
                items_v[i] = items_v[j];
                items_v[j] = temp_v;
                
                temp_name = items_name[i];
                items_name[i] = items_name[j];
                items_name[j] = temp_name;
            }
        }
    }
    
    for (i = 8; i >= 0; i = i - 1) {
        if (space > 0) {
            if (space >= items_w[i]) {
                space = space - items_w[i];
            } else {
                space = 0;
            }
        }
    }
    
    return;
}
