void ClientText(int handle, char *buf, int buf_len) {
    int i[5];
    int j[5];
    if (handle < 0 || handle >= 1024) {
        return;
    }
    j[0] = 0;
    
    for (i[0] = 0; i[0] < buf_len; i[0] = i[0] + 1) {
        if (handle < 0 || handle >= 1024) {
            return;
        }
        j[0] = j[0] + 1;
        
        if (j[0] == 4000) {
            while (1) {
                int ret[5];
                ret[0] = 0;
                if (ret[0] == 0) {
                    break;
                }
            }
            j[0] = 0;
        }
    }
    
    while (1) {
        int ret[5];
        ret[0] = 0;
        if (ret[0] == 0) {
            break;
        }
    }
    return;
}
