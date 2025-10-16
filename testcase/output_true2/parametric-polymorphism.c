int tree_insert(int root_value, int left, int right, int value) {
    int root[5] = {root_value, left, right, 0, 0};
    int n[5] = {value, 0, 0, 0, 0};
    int found = 0;
    
    for (found = 0; found < 5; found = found + 1) {
        if (root[0] < n[0]) {
            if (root[1] == 0) {
                root[1] = n[0];
                return root[1];
            } else {
                root[0] = root[1];
            }
        } else {
            if (root[2] == 0) {
                root[2] = n[0];
                return root[2];
            } else {
                root[0] = root[2];
            }
        }
    }
    return 0;
}
