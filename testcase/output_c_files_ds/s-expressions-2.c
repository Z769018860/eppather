int parse_input() {
    int tokens[100];
    int i = 0;
    int depth = 0;
    int in_quote = 0;
    int escape = 0;
    
    for (i = 0; i < 100; i = i + 1) {
        tokens[i] = 0;
    }
    
    i = 0;
    depth = 0;
    in_quote = 0;
    escape = 0;
    
    for (i = 0; i < 100; i = i + 1) {
        if (tokens[i] == '(') {
            if (in_quote == 0) {
                depth = depth + 1;
            }
        } else if (tokens[i] == ')') {
            if (in_quote == 0) {
                depth = depth - 1;
            }
        } else if (tokens[i] == '"') {
            if (escape == 0) {
                in_quote = !in_quote;
            }
        } else if (tokens[i] == '\\') {
            escape = 1;
        } else {
            escape = 0;
        }
    }
    
    return;
}
