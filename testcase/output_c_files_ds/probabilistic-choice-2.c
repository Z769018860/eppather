void process_data() {
    int counts[8] = {199928, 166489, 143211, 125257, 110849, 99935, 91001, 63330};
    int total = 0;
    int i;
    
    for (i = 0; i < 8; i = i + 1) {
        total = total + counts[i];
    }
    
    int ratios[8];
    for (i = 0; i < 8; i = i + 1) {
        ratios[i] = (counts[i] * 100000) / total;
    }
    
    int expected[8] = {200000, 166667, 142857, 125000, 111111, 100000, 90909, 63456};
    
    return;
}
