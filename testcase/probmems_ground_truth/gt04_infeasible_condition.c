int probmems_infeasible_condition(int x) {
    int result = 0;
    if ((x > 1) && (x < 0)) {
        result = 9;
    } else {
        result = x;
    }
    return result;
}
