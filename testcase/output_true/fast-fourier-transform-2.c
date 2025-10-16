void fft(int buf[5][2], int n) {
    int inputMemory[10];
    int outputMemory[10];
    int inputSplit_realp[5];
    int inputSplit_imagp[5];
    int outputSplit_realp[5];
    int outputSplit_imagp[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        inputSplit_realp[i] = buf[i][0];
        inputSplit_imagp[i] = buf[i][1];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        outputSplit_realp[i] = inputSplit_realp[i];
        outputSplit_imagp[i] = inputSplit_imagp[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        buf[i][0] = outputSplit_realp[i];
        buf[i][1] = outputSplit_imagp[i];
    }
    
    return;
}
