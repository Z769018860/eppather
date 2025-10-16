void deck_operations(int locale_ok_param, int n1, int n2, int n3, int n4, int n5) {
    int s_suits[4] = {9824, 9829, 9830, 9827};
    char s_suits_ascii[4][2] = {{'S'}, {'H'}, {'D'}, {'C'}};
    char s_nums[14][6] = {"WHAT", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int cards[52][3];
    int deck_n = 52;
    int i;
    int j;
    int k;
    
    for (i = 0; i < 4; i = i + 1) {
        for (j = 1; j <= 13; j = j + 1) {
            cards[k][0] = i;
            cards[k][1] = j;
            k = k + 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (locale_ok_param) {
                int suit = cards[i][0];
                int num = cards[i][1];
            } else {
                int suit = cards[i][0];
                int num = cards[i][1];
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        cards[i][2] = n1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (cards[i][2] > cards[j][2]) {
                int temp[3] = {cards[i][0], cards[i][1], cards[i][2]};
                cards[i][0] = cards[j][0];
                cards[i][1] = cards[j][1];
                cards[i][2] = cards[j][2];
                cards[j][0] = temp[0];
                cards[j][1] = temp[1];
                cards[j][2] = temp[2];
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        deck_n = deck_n - 1;
    }
    
    return;
}
