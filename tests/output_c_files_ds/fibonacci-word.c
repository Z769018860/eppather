void process_sequence() {
    int ones;
    int zeros;
    int total;
    int i;
    int j;
    int k;
    int n;
    int word_length;
    int last_word_length;
    int current_word_length;
    int next_word_length;
    char last_word[10000];
    char current_word[10000];
    char next_word[10000];
    
    last_word[0] = '1';
    last_word[1] = '\0';
    current_word[0] = '0';
    current_word[1] = '\0';
    
    for (n = 1; n <= 37; n = n + 1) {
        if (n == 1) {
            word_length = 1;
            ones = 0;
            zeros = 0;
            for (i = 0; last_word[i] != '\0'; i = i + 1) {
                if (last_word[i] == '0') {
                    zeros = zeros + 1;
                }
                if (last_word[i] == '1') {
                    ones = ones + 1;
                }
            }
            total = ones + zeros;
            if (total != 0) {
                if (ones == 0 || zeros == 0) {
                    ;
                }
            }
        } else {
            word_length = 0;
            for (i = 0; current_word[i] != '\0'; i = i + 1) {
                word_length = word_length + 1;
            }
            ones = 0;
            zeros = 0;
            for (i = 0; current_word[i] != '\0'; i = i + 1) {
                if (current_word[i] == '0') {
                    zeros = zeros + 1;
                }
                if (current_word[i] == '1') {
                    ones = ones + 1;
                }
            }
            total = ones + zeros;
            if (total != 0) {
                if (ones == 0 || zeros == 0) {
                    ;
                }
            }
            
            last_word_length = 0;
            for (i = 0; last_word[i] != '\0'; i = i + 1) {
                last_word_length = last_word_length + 1;
            }
            current_word_length = 0;
            for (i = 0; current_word[i] != '\0'; i = i + 1) {
                current_word_length = current_word_length + 1;
            }
            next_word_length = current_word_length + last_word_length;
            for (i = 0; i < current_word_length; i = i + 1) {
                next_word[i] = current_word[i];
            }
            for (j = 0; j < last_word_length; j = j + 1) {
                next_word[i + j] = last_word[j];
            }
            next_word[next_word_length] = '\0';
            
            for (k = 0; k <= current_word_length; k = k + 1) {
                last_word[k] = current_word[k];
            }
            for (k = 0; k <= next_word_length; k = k + 1) {
                current_word[k] = next_word[k];
            }
        }
    }
    return;
}
