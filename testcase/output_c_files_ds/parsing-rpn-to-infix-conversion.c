int precedenceCheck(char oper1, char oper2) {
    if (oper1 == oper2) {
        return 0;
    }
    if (oper1 == '^') {
        return 1;
    }
    if (oper2 == '^') {
        return 2;
    }
    if (oper1 == '/') {
        return 1;
    }
    if (oper2 == '/') {
        return 2;
    }
    if (oper1 == '*') {
        return 1;
    }
    if (oper2 == '*') {
        return 2;
    }
    if (oper1 == '+') {
        return 1;
    }
    if (oper2 == '+') {
        return 2;
    }
    if (oper1 == '-') {
        return 1;
    }
    return 2;
}

int isOperator(char c) {
    if (c == '+') {
        return 1;
    }
    if (c == '-') {
        return 1;
    }
    if (c == '*') {
        return 1;
    }
    if (c == '/') {
        return 1;
    }
    if (c == '^') {
        return 1;
    }
    return 0;
}

void processTree(int* tree_data, int* tree_left, int* tree_right, int pos, int* components, int* counter) {
    if (isOperator(components[pos]) == 1) {
        tree_data[pos] = components[pos];
        tree_right[pos] = *counter;
        *counter = *counter - 1;
        processTree(tree_data, tree_left, tree_right, tree_right[pos], components, counter);
        tree_left[pos] = *counter;
        *counter = *counter - 1;
        processTree(tree_data, tree_left, tree_right, tree_left[pos], components, counter);
    } else {
        tree_data[pos] = components[pos];
        tree_left[pos] = -1;
        tree_right[pos] = -1;
    }
}

int checkRPN(int* components, int counter) {
    int operSum = 0;
    int numberSum = 0;
    int i;
    
    if (isOperator(components[counter]) == 0) {
        return 0;
    }
    
    for (i = 0; i <= counter; i = i + 1) {
        if (isOperator(components[i]) == 1) {
            operSum = operSum + 1;
        } else {
            numberSum = numberSum + 1;
        }
    }
    
    if (numberSum - operSum == 1) {
        return 1;
    }
    return 0;
}

void buildStack(char* str, int* components, int* counter) {
    int i;
    int j;
    int k;
    int len;
    
    *counter = 0;
    for (i = 0; str[i] != 0; i = i + 1) {
        if (str[i] == ' ') {
            *counter = *counter + 1;
        }
    }
    
    j = 0;
    k = 0;
    len = 0;
    for (i = 0; str[i] != 0; i = i + 1) {
        if (str[i] == ' ') {
            components[k] = str[j];
            k = k + 1;
            j = i + 1;
            len = 0;
        } else {
            len = len + 1;
        }
    }
    components[k] = str[j];
    *counter = k;
}

void processInorder(int* tree_data, int* tree_left, int* tree_right, int pos) {
    if (pos != -1) {
        if (tree_left[pos] != -1 && isOperator(tree_data[tree_left[pos]]) == 1 && (precedenceCheck(tree_data[pos], tree_data[tree_left[pos]]) == 1 || (precedenceCheck(tree_data[pos], tree_data[tree_left[pos]]) == 0 && tree_data[pos] == '^'))) {
            processInorder(tree_data, tree_left, tree_right, tree_left[pos]);
        } else {
            processInorder(tree_data, tree_left, tree_right, tree_left[pos]);
        }
        processInorder(tree_data, tree_left, tree_right, tree_right[pos]);
    }
    return;
}

void mainFunction(char* str) {
    int components[100];
    int tree_data[100];
    int tree_left[100];
    int tree_right[100];
    int counter;
    int i;
    
    buildStack(str, components, &counter);
    
    if (checkRPN(components, counter) == 0) {
        return;
    }
    
    for (i = 0; i < 100; i = i + 1) {
        tree_data[i] = 0;
        tree_left[i] = -1;
        tree_right[i] = -1;
    }
    
    processTree(tree_data, tree_left, tree_right, counter, components, &counter);
    processInorder(tree_data, tree_left, tree_right, counter);
    return;
}
