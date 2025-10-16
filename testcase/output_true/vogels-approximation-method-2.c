int transportation_problem(int n_rows, int n_cols) {
    int supply[5] = {461, 277, 356, 488, 393};
    int demand[5] = {278, 60, 461, 116, 1060};
    int costs[5][5] = {
        {46, 74, 9, 28, 99},
        {12, 75, 6, 36, 48},
        {35, 199, 4, 5, 71},
        {61, 81, 44, 88, 9},
        {85, 60, 14, 25, 79}
    };
    int results[5][5] = {0};
    int total_cost = 0;
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (supply[i] < demand[j]) {
                results[i][j] = supply[i];
                demand[j] = demand[j] - supply[i];
                supply[i] = 0;
            } else {
                results[i][j] = demand[j];
                supply[i] = supply[i] - demand[j];
                demand[j] = 0;
            }
            total_cost = total_cost + results[i][j] * costs[i][j];
        }
    }
    
    return total_cost;
}
