int flatten_list(int from_is_list, int from_ival, int from_lst[100][2], int to_is_list, int to_ival, int to_lst[100][2]) {
    int i;
    int t[2];
    if (from_is_list == 0) {
        t[0] = from_is_list;
        t[1] = from_ival;
        to_lst[to_ival][0] = t[0];
        to_lst[to_ival][1] = t[1];
        to_ival = to_ival + 1;
    } else {
        for (i = 0; i < from_ival; i = i + 1) {
            to_ival = flatten_list(from_lst[i][0], from_lst[i][1], from_lst, to_is_list, to_ival, to_lst);
        }
    }
    return to_ival;
}
