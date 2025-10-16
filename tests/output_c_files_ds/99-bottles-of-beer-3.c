int beer_song() {
    int _;
    _ = 100;
    for (; _ > 0; _ = _ - 1) {
        int temp1 = _ - 1;
        char s1[2] = {'s', 0};
        char s2[2] = {'s', 0};
        char num_buf[4] = {0};
        if (temp1 != 0) {
            if (temp1 / 10 != 0) {
                num_buf[0] = temp1 / 10 + 48;
                num_buf[1] = temp1 % 10 + 48;
                num_buf[2] = 32;
            } else {
                num_buf[0] = temp1 % 10 + 48;
            }
        }
        char bottles[20] = {'b','o','t','t','l','e','s',' ','o','f',' ','b','e','e','r',' ','i','n',' ','t','h','e',' ','w','a','l','l',0};
        char no_more[11] = {'N','o',' ','m','o','r','e',' ','b','e','e','r','s',0};
        if (_ - 1 != 0) {
            if (_ - 1 != 1) {
                s1[0] = 's';
            } else {
                s1[0] = 0;
            }
            if (_ != 1) {
                s2[0] = 's';
            } else {
                s2[0] = 0;
            }
        } else {
            s1[0] = 0;
            s2[0] = 0;
        }
    }
    return;
}
