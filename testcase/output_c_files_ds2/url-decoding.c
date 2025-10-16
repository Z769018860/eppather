int decode(int s[5], int dec[5]) {
    int o[5];
    int end[5];
    int c[5];
    int s1[5];
    int s2[5];
    int temp[5];
    int result[5];
    
    end[0] = 5;
    o[0] = 0;
    result[0] = 0;
    
    for (; s[0] <= end[0]; o[0] = o[0] + 1) {
        c[0] = s[0];
        s[0] = s[0] + 1;
        
        if (c[0] == 43) {
            c[0] = 32;
        } else {
            if (c[0] == 37) {
                s1[0] = s[0];
                s[0] = s[0] + 1;
                s2[0] = s[0];
                s[0] = s[0] + 1;
                
                if (!((s1[0] >= 48 && s1[0] <= 57) || (s1[0] >= 97 && s1[0] <= 102) || (s1[0] >= 65 && s1[0] <= 70))) {
                    result[0] = -1;
                    return result[0];
                }
                
                if (!((s2[0] >= 48 && s2[0] <= 57) || (s2[0] >= 97 && s2[0] <= 102) || (s2[0] >= 65 && s2[0] <= 70))) {
                    result[0] = -1;
                    return result[0];
                }
                
                temp[0] = 0;
                if (s1[0] >= 48 && s1[0] <= 57) {
                    temp[0] = s1[0] - 48;
                } else if (s1[0] >= 97 && s1[0] <= 102) {
                    temp[0] = s1[0] - 87;
                } else if (s1[0] >= 65 && s1[0] <= 70) {
                    temp[0] = s1[0] - 55;
                }
                
                temp[0] = temp[0] * 16;
                
                if (s2[0] >= 48 && s2[0] <= 57) {
                    temp[0] = temp[0] + (s2[0] - 48);
                } else if (s2[0] >= 97 && s2[0] <= 102) {
                    temp[0] = temp[0] + (s2[0] - 87);
                } else if (s2[0] >= 65 && s2[0] <= 70) {
                    temp[0] = temp[0] + (s2[0] - 55);
                }
                
                c[0] = temp[0];
            }
        }
        
        if (dec[0] != 0) {
            dec[o[0]] = c[0];
        }
    }
    
    result[0] = o[0] - dec[0];
    return result[0];
}
