int guess_game(int n, int g, int c) {
    int arr[5];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    arr[4] = 0;
    
    for (arr[0] = 0; arr[0] < 5; arr[0] = arr[0] + 1) {
        if (g != n) {
            arr[1] = 1;
        } else {
            arr[1] = 0;
        }
        
        if (arr[1] == 1) {
            arr[2] = 0;
        } else {
            return 0;
        }
        
        if (c != 0) {
            arr[3] = 1;
        } else {
            arr[3] = 0;
        }
        
        if (arr[3] == 1) {
            arr[4] = 1;
        } else {
            arr[4] = 0;
        }
    }
    return 0;
}
