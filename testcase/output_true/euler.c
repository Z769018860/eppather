void solve_euler_check_result(int timestep_param, int threshold_param, int n_param, int result[5], int is_approx[5]) {
    int i;
    int timestep = timestep_param;
    int threshold = threshold_param;
    int n = n_param;
    
    if (n != 0) {
        result[0] = 1000;
        for (i = 1; i < 5; i = i + 1) {
            result[i] = result[i - 1] - 3 * result[i - 1] * timestep / 1000;
        }
    }
    
    is_approx[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        int solution = 1000;
        int j;
        for (j = 0; j < i; j = j + 1) {
            solution = solution - 3 * solution * timestep / 1000;
        }
        if ((result[i] - solution) > threshold || (solution - result[i]) > threshold) {
            is_approx[0] = 0;
        }
    }
    
    return;
}
