void process_data(int counts[8], int ratios[8], int expected[8]) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        counts[i] = 0;
        ratios[i] = 0;
        expected[i] = 0;
    }
    counts[0] = 199928;
    counts[1] = 166489;
    counts[2] = 143211;
    counts[3] = 125257;
    counts[4] = 110849;
    counts[5] = 99935;
    counts[6] = 91001;
    counts[7] = 63330;
    
    ratios[0] = 199928;
    ratios[1] = 166489;
    ratios[2] = 143211;
    ratios[3] = 125257;
    ratios[4] = 110849;
    ratios[5] = 99935;
    ratios[6] = 91001;
    ratios[7] = 63330;
    
    expected[0] = 200000;
    expected[1] = 166667;
    expected[2] = 142857;
    expected[3] = 125000;
    expected[4] = 111111;
    expected[5] = 100000;
    expected[6] = 90909;
    expected[7] = 63456;
    
    return;
}
