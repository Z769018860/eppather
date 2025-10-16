int varint_encode_decode(int input) {
    int buffer[5];
    buffer[0] = 0;
    int output[5];
    output[0] = 0;
    int i;
    int j;
    int temp[5];
    temp[0] = input;
    
    if (temp[0] == 0) {
        buffer[0] = 0;
    } else {
        for (i = 0; i < 5; i = i + 1) {
            if (temp[0] > 0) {
                buffer[i] = (temp[0] & 127) | 128;
                temp[0] = temp[0] >> 7;
            } else {
                buffer[i] = temp[0] & 127;
                temp[0] = 0;
            }
            if (temp[0] == 0) {
                break;
            }
        }
    }
    
    for (j = i; j >= 0; j = j - 1) {
        output[0] = (output[0] << 7) | (buffer[j] & 127);
    }
    
    return output[0];
}
