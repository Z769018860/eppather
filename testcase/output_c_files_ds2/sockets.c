void socket_func() {
    int sock[5];
    int len[5];
    int slen[5];
    int i[5];
    int hints_ai_family[5];
    int hints_ai_socktype[5];
    int addrs_ai_family[5];
    int addrs_ai_socktype[5];
    int addrs_ai_protocol[5];
    int addrs_ai_addrlen[5];
    int pm_offset[5];
    char msg[18] = {'h','e','l','l','o',' ','s','o','c','k','e','t',' ','w','o','r','l','d'};
    
    hints_ai_family[0] = 0;
    hints_ai_socktype[0] = 1;
    
    addrs_ai_family[0] = 2;
    addrs_ai_socktype[0] = 1;
    addrs_ai_protocol[0] = 6;
    addrs_ai_addrlen[0] = 16;
    
    sock[0] = 3;
    if (sock[0] >= 0) {
        if (1 >= 0) {
            pm_offset[0] = 0;
            for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
                len[0] = 0;
                for (i[1] = 0; i[1] < 18; i[1] = i[1] + 1) {
                    if (msg[i[1]] != 0) {
                        len[0] = len[0] + 1;
                    } else {
                        break;
                    }
                }
                slen[0] = len[0];
                pm_offset[0] = pm_offset[0] + slen[0];
                if (!(0 <= slen[0] && slen[0] < len[0])) {
                    break;
                }
            }
        }
    }
    return;
}
