void process_input() {
    char input[342] = "Character,Speech\nThe multitude,The messiah! Show us the messiah!\nBrians mother,<angry>Now you listen here! He's not the messiah; he's a very naughty boy! Now go away!</angry>\nThe multitude,Who are you?\nBrians mother,I'm his mother; that's who!\nThe multitude,Behold his mother! Behold his mother!";
    char output[2000];
    int i;
    int j = 0;
    
    for (i = 0; i < 342; i = i + 1) {
        if (input[i] == '\0') {
            break;
        }
        if (input[i] == '\n') {
            output[j] = '<';
            j = j + 1;
            output[j] = '/';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'd';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
            output[j] = '<';
            j = j + 1;
            output[j] = '/';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'r';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
            output[j] = '\n';
            j = j + 1;
            output[j] = '<';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'r';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
            output[j] = '<';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'd';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
        } else if (input[i] == ',') {
            output[j] = '<';
            j = j + 1;
            output[j] = '/';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'd';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
            output[j] = '<';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = 'd';
            j = j + 1;
            output[j] = '>';
            j = j + 1;
        } else if (input[i] == '<') {
            output[j] = '&';
            j = j + 1;
            output[j] = 'l';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = ';';
            j = j + 1;
        } else if (input[i] == '>') {
            output[j] = '&';
            j = j + 1;
            output[j] = 'g';
            j = j + 1;
            output[j] = 't';
            j = j + 1;
            output[j] = ';';
            j = j + 1;
        } else if (input[i] == '&') {
            output[j] = '&';
            j = j + 1;
            output[j] = 'a';
            j = j + 1;
            output[j] = 'm';
            j = j + 1;
            output[j] = 'p';
            j = j + 1;
            output[j] = ';';
            j = j + 1;
        } else {
            output[j] = input[i];
            j = j + 1;
        }
    }
    output[j] = '<';
    j = j + 1;
    output[j] = '/';
    j = j + 1;
    output[j] = 't';
    j = j + 1;
    output[j] = 'd';
    j = j + 1;
    output[j] = '>';
    j = j + 1;
    output[j] = '\n';
    j = j + 1;
    output[j] = '<';
    j = j + 1;
    output[j] = '/';
    j = j + 1;
    output[j] = 't';
    j = j + 1;
    output[j] = 'r';
    j = j + 1;
    output[j] = '>';
    j = j + 1;
    return;
}
