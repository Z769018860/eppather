int flatten_list(int from_is_list, int from_ival, int from_lst[5][5], int to_is_list, int to_ival, int to_lst[5][5]) {
    int i;
    int t_is_list[5];
    int t_ival[5];
    int t_lst[5][5];
    
    if (from_is_list == 0) {
        t_is_list[0] = from_is_list;
        t_ival[0] = from_ival;
        for (i = 0; i < 5; i = i + 1) {
            t_lst[0][i] = from_lst[0][i];
        }
        to_is_list = 1;
        to_ival = to_ival + 1;
        for (i = 0; i < 5; i = i + 1) {
            to_lst[to_ival - 1][i] = t_lst[0][i];
        }
    } else {
        for (i = 0; i < from_ival; i = i + 1) {
            flatten_list(from_lst[i][0], from_lst[i][1], from_lst, to_is_list, to_ival, to_lst);
        }
    }
    return;
}
