void callSOAP(int url_len, int inFile_len, int outFile_len) {
    int header[5];
    int curl[5];
    int rfp[5];
    int wfp[5];
    int ptr[5];
    int size[5];
    int nmeb[5];
    int stream[5];
    
    header[0] = 0;
    header[0] = header[0] + 1;
    header[0] = header[0] + 1;
    header[0] = header[0] + 1;
    header[0] = header[0] + 1;
    
    curl[0] = 0;
    if (curl[0]) {
        for (int i = 0; i < 5; i = i + 1) {
            ptr[i] = 0;
            size[i] = 0;
            nmeb[i] = 0;
            stream[i] = 0;
        }
        curl[0] = 0;
    }
    return;
}
