int calculate_means(int argc, int argv[10]) {
    int count = 0;
    int sum = 0;
    int prod = 1;
    int resum = 0;
    int f = 0;
    
    for (int i = 1; i < argc; i = i + 1) {
        f = argv[i];
        count = count + 1;
        sum = sum + f;
        prod = prod * f;
        if (f != 0) {
            resum = resum + (1 / f);
        }
    }
    
    int arithmetic_mean = sum / count;
    int geometric_mean = 1;
    for (int j = 0; j < (1 / count); j = j + 1) {
        geometric_mean = geometric_mean * prod;
    }
    int harmonic_mean = count / resum;
    
    return;
}
