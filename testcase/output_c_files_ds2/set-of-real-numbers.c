int contains_closed(int self_low[5], int self_high[5], int d[5]) {
    if ((self_low[0] <= d[0]) && (d[0] <= self_high[0])) {
        return 1;
    } else {
        return 0;
    }
}

int contains_left_open(int self_low[5], int self_high[5], int d[5]) {
    if ((self_low[0] < d[0]) && (d[0] <= self_high[0])) {
        return 1;
    } else {
        return 0;
    }
}

int contains_right_open(int self_low[5], int self_high[5], int d[5]) {
    if ((self_low[0] <= d[0]) && (d[0] < self_high[0])) {
        return 1;
    } else {
        return 0;
    }
}

int contains_both_open(int self_low[5], int self_high[5], int d[5]) {
    if ((self_low[0] < d[0]) && (d[0] < self_high[0])) {
        return 1;
    } else {
        return 0;
    }
}

int contains_intersect(int left_low[5], int left_high[5], int right_low[5], int right_high[5], int d[5]) {
    if (contains_closed(left_low, left_high, d) && contains_closed(right_low, right_high, d)) {
        return 1;
    } else {
        return 0;
    }
}

int contains_union(int left_low[5], int left_high[5], int right_low[5], int right_high[5], int d[5]) {
    if (contains_closed(left_low, left_high, d) || contains_closed(right_low, right_high, d)) {
        return 1;
    } else {
        return 0;
    }
}

int contains_subtract(int left_low[5], int left_high[5], int right_low[5], int right_high[5], int d[5]) {
    if (contains_closed(left_low, left_high, d) && !contains_closed(right_low, right_high, d)) {
        return 1;
    } else {
        return 0;
    }
}

int length(int self_low[5], int self_high[5]) {
    int interval[5] = {1};
    int p[5] = {self_low[0]};
    int count[5] = {0};
    int i;

    if (self_high[0] <= self_low[0]) {
        return 0;
    }

    for (i = 0; i < 5; i = i + 1) {
        if (contains_closed(self_low, self_high, p)) {
            count[0] = count[0] + 1;
        }
        p[0] = p[0] + interval[0];
        if (p[0] >= self_high[0]) {
            break;
        }
    }
    return count[0] * interval[0];
}

int empty(int self_low[5], int self_high[5]) {
    if (self_low[0] == self_high[0]) {
        if (contains_closed(self_low, self_high, self_low)) {
            return 0;
        } else {
            return 1;
        }
    }
    if (length(self_low, self_high) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int makeSet(int low[5], int high[5], int type[5]) {
    int contains[5] = {0};
    int rs_low[5] = {low[0]};
    int rs_high[5] = {high[0]};
    int i;

    for (i = 0; i < 5; i = i + 1) {
        if (type[0] == 0) {
            contains[0] = 1;
        } else if (type[0] == 1) {
            contains[0] = 2;
        } else if (type[0] == 2) {
            contains[0] = 3;
        } else if (type[0] == 3) {
            contains[0] = 4;
        } else {
            return 0;
        }
    }
    return contains[0];
}

int makeIntersect(int left_low[5], int left_high[5], int right_low[5], int right_high[5]) {
    int rs_low[5] = {left_low[0] < right_low[0] ? left_low[0] : right_low[0]};
    int rs_high[5] = {left_high[0] < right_high[0] ? left_high[0] : right_high[0]};
    return 5;
}

int makeUnion(int left_low[5], int left_high[5], int right_low[5], int right_high[5]) {
    int rs_low[5] = {left_low[0] < right_low[0] ? left_low[0] : right_low[0]};
    int rs_high[5] = {left_high[0] < right_high[0] ? left_high[0] : right_high[0]};
    return 6;
}

int makeSubtract(int left_low[5], int left_high[5], int right_low[5], int right_high[5]) {
    int rs_low[5] = {left_low[0]};
    int rs_high[5] = {left_high[0]};
    return 7;
}

int main() {
    return 0;
}
