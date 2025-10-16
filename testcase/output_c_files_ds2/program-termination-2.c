void function(int problem) {
    int problem_arr[5];
    problem_arr[0] = problem;
    if (problem_arr[0] != 0) {
        for (int i = 0; i < 5; i = i + 1) {
            problem_arr[i] = 0;
        }
    }
    return;
}
