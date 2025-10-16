int greedy_wrap(int words_s[5], int words_len[5], int count, int cols, int breaks[5]) {
    int score = 0;
    int line = 0;
    int i = 0;
    int j = 0;
    int d = 0;
    
    for (;;) {
        if (i == count) {
            breaks[j] = i;
            j = j + 1;
            break;
        }
        
        if (line == 0) {
            line = words_len[i];
            i = i + 1;
            continue;
        }
        
        if (line + words_len[i] < cols) {
            line = line + words_len[i] + 1;
            i = i + 1;
            continue;
        }
        
        breaks[j] = i;
        j = j + 1;
        if (i < count) {
            d = cols - line;
            if (d > 0) {
                score = score + 1 * d * d;
            } else {
                if (d < 0) {
                    score = score + 100 * d * d;
                }
            }
        }
        
        line = 0;
    }
    
    breaks[j] = 0;
    j = j + 1;
    return score;
}

int balanced_wrap(int words_s[5], int words_len[5], int count, int cols, int breaks[5]) {
    int best[5];
    int best_score = greedy_wrap(words_s, words_len, count, cols, breaks);
    int line = 0;
    int start = 0;
    int score = 0;
    int current_score = 0;
    int d = 0;
    int line_no = 0;
    int i = 0;
    
    for (;;) {
        if (line) {
            line = line + 1;
        }
        line = line + words_len[start];
        start = start + 1;
        d = cols - line;
        if (start < count || d < 0) {
            if (d > 0) {
                current_score = score + 1 * d * d;
            } else {
                current_score = score + 100 * d * d;
            }
        } else {
            current_score = score;
        }
        
        if (current_score >= best_score) {
            if (d <= 0) {
                break;
            }
            continue;
        }
        
        best[line_no] = start;
        line_no = line_no + 1;
        score = current_score;
    }
    
    if (current_score >= 0 && current_score < best_score) {
        best_score = current_score;
        for (i = 0; i < line_no; i = i + 1) {
            breaks[i] = best[i];
        }
    }
    
    return best_score;
}

void show_wrap(int words_s[5], int words_len[5], int count, int breaks[5]) {
    int i = 0;
    int j = 0;
    
    for (i = 0; i < count && breaks[i]; i = i + 1) {
        for (j = j; j < breaks[i]; j = j + 1) {
            if (j < breaks[i] - 1) {
            }
        }
        if (breaks[i]) {
        }
    }
    
    return;
}

int make_word_list(int s[5], int n[5]) {
    int max_n = 0;
    int words_s[5];
    int words_len[5];
    int i = 0;
    
    n[0] = 0;
    for (;;) {
        for (; s[i] && (s[i] == 32 || s[i] == 9 || s[i] == 10 || s[i] == 13); i = i + 1) {
        }
        if (!s[i]) {
            break;
        }
        
        if (n[0] >= max_n) {
            if (!(max_n = max_n * 2)) {
                max_n = 2;
            }
        }
        words_s[n[0]] = s[i];
        for (; s[i] && !(s[i] == 32 || s[i] == 9 || s[i] == 10 || s[i] == 13); i = i + 1) {
        }
        words_len[n[0]] = i - words_s[n[0]];
        n[0] = n[0] + 1;
    }
    
    return 0;
}

return;
