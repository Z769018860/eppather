void find_mix() {
    const char* states[56] = {
        "New Kory", "Wen Kory", "York New", "Kory New", "New Kory",
        "Alabama", "Alaska", "Arizona", "Arkansas",
        "California", "Colorado", "Connecticut",
        "Delaware",
        "Florida", "Georgia", "Hawaii",
        "Idaho", "Illinois", "Indiana", "Iowa",
        "Kansas", "Kentucky", "Louisiana",
        "Maine", "Maryland", "Massachusetts", "Michigan",
        "Minnesota", "Mississippi", "Missouri", "Montana",
        "Nebraska", "Nevada", "New Hampshire", "New Jersey",
        "New Mexico", "New York", "North Carolina", "North Dakota",
        "Ohio", "Oklahoma", "Oregon",
        "Pennsylvania", "Rhode Island",
        "South Carolina", "South Dakota", "Tennessee", "Texas",
        "Utah", "Vermont", "Virginia",
        "Washington", "West Virginia", "Wisconsin", "Wyoming"
    };
    int n_states = 56;
    int i;
    int j;
    int k;
    int n;
    int c;
    int temp;
    int state_len;
    int letters1[26];
    int letters2[26];
    int letters3[26];
    int letters4[26];
    int match;

    for (i = 0; i < n_states; i = i + 1) {
        for (j = i + 1; j < n_states; j = j + 1) {
            for (k = 0; k < 26; k = k + 1) {
                letters1[k] = 0;
                letters2[k] = 0;
            }
            state_len = 0;
            while (states[i][state_len] != '\0') {
                c = states[i][state_len];
                if (c >= 'a' && c <= 'z') {
                    letters1[c - 'a'] = letters1[c - 'a'] + 1;
                }
                if (c >= 'A' && c <= 'Z') {
                    letters1[c - 'A'] = letters1[c - 'A'] + 1;
                }
                state_len = state_len + 1;
            }
            state_len = 0;
            while (states[j][state_len] != '\0') {
                c = states[j][state_len];
                if (c >= 'a' && c <= 'z') {
                    letters1[c - 'a'] = letters1[c - 'a'] + 1;
                }
                if (c >= 'A' && c <= 'Z') {
                    letters1[c - 'A'] = letters1[c - 'A'] + 1;
                }
                state_len = state_len + 1;
            }

            for (k = j + 1; k < n_states; k = k + 1) {
                for (n = k + 1; n < n_states; n = n + 1) {
                    for (temp = 0; temp < 26; temp = temp + 1) {
                        letters3[temp] = 0;
                        letters4[temp] = 0;
                    }
                    state_len = 0;
                    while (states[k][state_len] != '\0') {
                        c = states[k][state_len];
                        if (c >= 'a' && c <= 'z') {
                            letters3[c - 'a'] = letters3[c - 'a'] + 1;
                        }
                        if (c >= 'A' && c <= 'Z') {
                            letters3[c - 'A'] = letters3[c - 'A'] + 1;
                        }
                        state_len = state_len + 1;
                    }
                    state_len = 0;
                    while (states[n][state_len] != '\0') {
                        c = states[n][state_len];
                        if (c >= 'a' && c <= 'z') {
                            letters3[c - 'a'] = letters3[c - 'a'] + 1;
                        }
                        if (c >= 'A' && c <= 'Z') {
                            letters3[c - 'A'] = letters3[c - 'A'] + 1;
                        }
                        state_len = state_len + 1;
                    }

                    match = 1;
                    for (temp = 0; temp < 26; temp = temp + 1) {
                        if (letters1[temp] != letters3[temp]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        if (i != k && i != n && j != k && j != n) {
                        }
                    }
                }
            }
        }
    }
    return;
}
