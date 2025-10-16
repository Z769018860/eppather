void solve_euler_and_check(int timestep_int, int result[100], int threshold_int, int n) {
    int i;
    int timestep;
    int threshold;
    timestep = timestep_int;
    threshold = threshold_int;
    
    if (n != 0) {
        result[0] = 1000;
        for (i = 1; i < n; i = i + 1) {
            result[i] = result[i-1] - 3 * result[i-1] * timestep / 1000;
        }
    }
    
    int is_approx;
    is_approx = 1;
    for (i = 0; i < n; i = i + 1) {
        int solution;
        int term;
        int diff;
        
        term = 3 * i * timestep;
        solution = 1000 - term + (term * term) / 2000 - (term * term * term) / 6000000;
        
        if (result[i] > solution) {
            diff = result[i] - solution;
        } else {
            diff = solution - result[i];
        }
        
        if (diff > threshold) {
            is_approx = 0;
        }
    }
    
    return;
}
