void http_server(int port) {
    int sock[5];
    int client_fd[5];
    int one[5] = {1,0,0,0,0};
    int svr_addr[5];
    int cli_addr[5];
    int sin_len[5] = {5,0,0,0,0};
    
    sock[0] = 0;
    client_fd[0] = 0;
    svr_addr[0] = 0;
    cli_addr[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        sock[0] = sock[0] + 1;
        if (sock[0] < 0) {
            return;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        svr_addr[0] = svr_addr[0] + 1;
        svr_addr[1] = svr_addr[1] + 1;
        svr_addr[2] = svr_addr[2] + 1;
        svr_addr[3] = svr_addr[3] + 1;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (svr_addr[0] == -1) {
            return;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        client_fd[0] = sock[0];
        if (client_fd[0] == -1) {
            continue;
        }
    }
    
    return;
}
