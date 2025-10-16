int solve(int person, int verbose, int n_floors, int n_conditions)
{
    int solution[5] = {0};
    int occupied[5] = {0};
    int i;
    int j;
    int top = n_floors - 1;
    
    if (person == 5) {
        for (i = 0; i < n_conditions; i = i + 1) {
            int cond_result = 0;
            if (i == 0) {
                if (solution[0] != top) {
                    cond_result = 1;
                }
            }
            if (i == 1) {
                if (solution[1] != 0) {
                    cond_result = 1;
                }
            }
            if (i == 2) {
                if (solution[2] != 0 && solution[2] != top) {
                    cond_result = 1;
                }
            }
            if (i == 3) {
                if (solution[3] > solution[1]) {
                    cond_result = 1;
                }
            }
            if (i == 4) {
                int diff = solution[4] - solution[2];
                if (diff < 0) {
                    diff = -diff;
                }
                if (diff != 1) {
                    cond_result = 1;
                }
            }
            if (i == 5) {
                int diff = solution[1] - solution[2];
                if (diff < 0) {
                    diff = -diff;
                }
                if (diff != 1) {
                    cond_result = 1;
                }
            }
            if (cond_result == 0) {
                return 0;
            }
        }
        return 1;
    }

    for (i = 0; i < n_floors; i = i + 1) {
        if (occupied[i] != 0) {
            continue;
        }
        solution[person] = i;
        occupied[i] = 1;
        if (solve(person + 1, verbose, n_floors, n_conditions) != 0) {
            return 1;
        }
        occupied[i] = 0;
    }
    return 0;
}
