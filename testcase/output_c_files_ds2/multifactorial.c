int multifact(int n, int deg) {
    int result[5];
    result[0] = n;
    if (n <= deg) {
        result[0] = n;
    } else {
        int temp[5];
        temp[0] = multifact(n - deg, deg);
        result[0] = n * temp[0];
    }
    return result[0];
}

int multifact_i(int n, int deg) {
    int result[5];
    result[0] = n;
    int n1[5];
    n1[0] = n;
    for (; n1[0] >= deg + 1; n1[0] = n1[0] - 1) {
        result[0] = result[0] * (n1[0] - deg);
        n1[0] = n1[0] - deg;
        n1[0] = n1[0] + deg;
    }
    return result[0];
}

void combined_multifact() {
    int i[5];
    int j[5];
    int highest_degree[5];
    highest_degree[0] = 5;
    int largest_number[5];
    largest_number[0] = 10;
    for (i[0] = 1; i[0] <= highest_degree[0]; i[0] = i[0] + 1) {
        for (j[0] = 1; j[0] <= largest_number[0]; j[0] = j[0] + 1) {
            int temp[5];
            temp[0] = multifact(j[0], i[0]);
        }
    }
    return;
}
