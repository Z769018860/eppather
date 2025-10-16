int real_set_contains(int set_type, double low, double high, double d) {
    if (set_type == 0) {
        if (low <= d && d <= high) {
            return 1;
        } else {
            return 0;
        }
    } else if (set_type == 1) {
        if (low < d && d <= high) {
            return 1;
        } else {
            return 0;
        }
    } else if (set_type == 2) {
        if (low <= d && d < high) {
            return 1;
        } else {
            return 0;
        }
    } else if (set_type == 3) {
        if (low < d && d < high) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int real_set_intersect_contains(int left_type, double left_low, double left_high, int right_type, double right_low, double right_high, double d) {
    int left_contains = real_set_contains(left_type, left_low, left_high, d);
    int right_contains = real_set_contains(right_type, right_low, right_high, d);
    if (left_contains && right_contains) {
        return 1;
    } else {
        return 0;
    }
}

int real_set_union_contains(int left_type, double left_low, double left_high, int right_type, double right_low, double right_high, double d) {
    int left_contains = real_set_contains(left_type, left_low, left_high, d);
    int right_contains = real_set_contains(right_type, right_low, right_high, d);
    if (left_contains || right_contains) {
        return 1;
    } else {
        return 0;
    }
}

int real_set_subtract_contains(int left_type, double left_low, double left_high, int right_type, double right_low, double right_high, double d) {
    int left_contains = real_set_contains(left_type, left_low, left_high, d);
    int right_contains = real_set_contains(right_type, right_low, right_high, d);
    if (left_contains && !right_contains) {
        return 1;
    } else {
        return 0;
    }
}

double real_set_length(int set_type, double low, double high) {
    double interval = 0.00001;
    double p = low;
    int count = 0;
    if (high <= low) {
        return 0.0;
    }
    for (; p < high; p = p + interval) {
        if (real_set_contains(set_type, low, high, p)) {
            count = count + 1;
        }
    }
    return count * interval;
}

int real_set_empty(int set_type, double low, double high) {
    if (low == high) {
        if (!real_set_contains(set_type, low, high, low)) {
            return 1;
        } else {
            return 0;
        }
    }
    if (real_set_length(set_type, low, high) == 0.0) {
        return 1;
    } else {
        return 0;
    }
}

return;
