int gcd_iter(int u, int v) {
    int u_arr[5];
    int v_arr[5];
    u_arr[0] = u;
    v_arr[0] = v;
    
    if (u_arr[0] < 0) {
        u_arr[0] = -u_arr[0];
    }
    if (v_arr[0] < 0) {
        v_arr[0] = -v_arr[0];
    }
    if (v_arr[0]) {
        for (int i = 0; i < 5; i = i + 1) {
            u_arr[0] = u_arr[0] % v_arr[0];
            if (u_arr[0] == 0) {
                break;
            }
            v_arr[0] = v_arr[0] % u_arr[0];
            if (v_arr[0] == 0) {
                break;
            }
        }
    }
    return (u_arr[0] + v_arr[0]);
}
