int function() {
    int two[1];
    int three[1];
    int four[1];
    int five[1];
    int answer[1];
    int context[1];
    int length;
    int string[20];
    
    two[0] = 2;
    three[0] = 3;
    four[0] = 4;
    five[0] = 5;
    
    answer[0] = three[0];
    for (int i = 0; i < two[0]; i = i + 1) {
        answer[0] = answer[0] * three[0];
    }
    
    for (int i = 0; i < answer[0]; i = i + 1) {
        four[0] = four[0] * four[0];
    }
    
    for (int i = 0; i < four[0]; i = i + 1) {
        five[0] = five[0] * five[0];
    }
    
    answer[0] = five[0];
    length = 0;
    for (int temp = answer[0]; temp != 0; temp = temp / 10) {
        length = length + 1;
    }
    
    return;
}
