int process_ie_ei_rule(char input[1000]) {
    int cie = 0;
    int cei = 0;
    int ie = 0;
    int ei = 0;
    int i = 0;
    
    for (i = 0; i < 1000; i = i + 1) {
        if (input[i] == '\0') {
            break;
        }
        if (i + 2 < 1000) {
            if ((input[i] == 'c' || input[i] == 'C') && (input[i + 1] == 'i' || input[i + 1] == 'I') && (input[i + 2] == 'e' || input[i + 2] == 'E')) {
                cie = cie + 1;
                ie = ie + 1;
                i = i + 2;
                continue;
            }
            if ((input[i] == 'c' || input[i] == 'C') && (input[i + 1] == 'e' || input[i + 1] == 'E') && (input[i + 2] == 'i' || input[i + 2] == 'I')) {
                cei = cei + 1;
                ei = ei + 1;
                i = i + 2;
                continue;
            }
        }
        if (i + 1 < 1000) {
            if ((input[i] == 'i' || input[i] == 'I') && (input[i + 1] == 'e' || input[i + 1] == 'E')) {
                ie = ie + 1;
                i = i + 1;
                continue;
            }
            if ((input[i] == 'e' || input[i] == 'E') && (input[i + 1] == 'i' || input[i + 1] == 'I')) {
                ei = ei + 1;
                i = i + 1;
                continue;
            }
        }
    }
    return;
}
