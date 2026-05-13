void compare_percentages(int counts[2]) {
    int total;
    total = counts[0] + counts[1];
    int percentages[2];
    percentages[0] = (counts[0] * 1000000) / total;
    percentages[1] = (counts[1] * 1000000) / total;
    return;
}
