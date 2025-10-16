void benford_distribution_actual_distribution(int prob[9], int freq[9], int tally[9], int total) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i < 9) {
            prob[i] = 0;
            freq[i] = 0;
            tally[i] = 0;
        }
    }
    total = 0;

    for (i = 1; i < 10; i = i + 1) {
        if (i - 1 < 9) {
            prob[i - 1] = 0;
        }
    }

    for (i = 0; i < 9; i = i + 1) {
        if (i < 9) {
            freq[i] = 0;
        }
    }
    return;
}
