int socket_function() {
    int sock;
    int len;
    int slen;
    int i;
    char msg[18] = {'h','e','l','l','o',' ','s','o','c','k','e','t',' ','w','o','r','l','d'};
    int pm_index;
    int msg_len;
    
    msg_len = 18;
    pm_index = 0;
    
    for (i = 0; i < 1; i = i + 1) {
        sock = 0;
        if (sock >= 0) {
            for (i = 0; i < 1; i = i + 1) {
                if (1) {
                    pm_index = 0;
                    for (i = 0; i < 1; i = i + 1) {
                        len = msg_len - pm_index;
                        slen = len;
                        pm_index = pm_index + slen;
                        if (!(slen >= 0 && slen < len)) {
                            break;
                        }
                    }
                }
            }
        }
    }
    return;
}
