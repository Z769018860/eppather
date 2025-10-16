void cameraPhoneFunction(int n1, int n2, int n3) {
    int cameraSample[3];
    cameraSample[0] = 0;
    cameraSample[1] = 0;
    cameraSample[2] = 0;
    
    int phoneSample[3];
    phoneSample[0] = 0;
    phoneSample[1] = 0;
    phoneSample[2] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i < n1) {
            cameraSample[0] = cameraSample[0] + 1;
        }
        if (i < n2) {
            cameraSample[1] = cameraSample[1] + 1;
        }
        if (i < n3) {
            cameraSample[2] = cameraSample[2] + 1;
        }
    }
    
    for (int j = 0; j < 5; j = j + 1) {
        if (j < n1) {
            phoneSample[0] = phoneSample[0] + 1;
        }
        if (j < n2) {
            phoneSample[1] = phoneSample[1] + 1;
        }
        if (j < n3) {
            phoneSample[2] = phoneSample[2] + 1;
        }
    }
    
    return;
}
