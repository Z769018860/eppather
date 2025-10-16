int precedenceCheck(int oper1, int oper2) {
    int result;
    if (oper1 == oper2) {
        result = 0;
    } else {
        if (oper1 == 94) {
            result = 1;
        } else {
            if (oper2 == 94) {
                result = 2;
            } else {
                if (oper1 == 47) {
                    result = 1;
                } else {
                    if (oper2 == 47) {
                        result = 2;
                    } else {
                        if (oper1 == 42) {
                            result = 1;
                        } else {
                            if (oper2 == 42) {
                                result = 2;
                            } else {
                                if (oper1 == 43) {
                                    result = 1;
                                } else {
                                    if (oper2 == 43) {
                                        result = 2;
                                    } else {
                                        if (oper1 == 45) {
                                            result = 1;
                                        } else {
                                            result = 2;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

int isOperator(int c) {
    int result;
    if (c == 43 || c == 45 || c == 42 || c == 47 || c == 94) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void inorder(int t_data[5], int t_left[5], int t_right[5]) {
    if (t_data[0] != 0) {
        if (t_left[0] != 0 && isOperator(t_left[0]) == 1 && (precedenceCheck(t_data[0], t_left[0]) == 1 || (precedenceCheck(t_data[0], t_left[0]) == 0 && t_data[0] == 94))) {
            inorder(t_left, t_left, t_right);
        } else {
            inorder(t_left, t_left, t_right);
        }
        if (t_right[0] != 0 && isOperator(t_right[0]) == 1 && (precedenceCheck(t_data[0], t_right[0]) == 1 || (precedenceCheck(t_data[0], t_right[0]) == 0 && t_data[0] != 94))) {
            inorder(t_right, t_left, t_right);
        } else {
            inorder(t_right, t_left, t_right);
        }
    }
    return;
}

int checkRPN(int components[5][5], int counter) {
    int operSum[5];
    int numberSum[5];
    int i;
    operSum[0] = 0;
    numberSum[0] = 0;
    if (isOperator(components[counter][0]) == 0) {
        return 0;
    }
    for (i = 0; i <= counter; i = i + 1) {
        if (isOperator(components[i][0]) == 1) {
            operSum[0] = operSum[0] + 1;
        } else {
            numberSum[0] = numberSum[0] + 1;
        }
    }
    if (numberSum[0] - operSum[0] == 1) {
        return 1;
    } else {
        return 0;
    }
}

void buildStack(int str[5], int components[5][5], int counter) {
    int i;
    int j;
    int k;
    k = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (str[i] == 32) {
            counter = counter + 1;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            components[i][j] = 0;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        if (str[i] != 32 && str[i] != 0) {
            components[k][0] = str[i];
            k = k + 1;
        }
    }
    return;
}

void buildTree(int obj[5], int trace[5], int t_data[5], int t_left[5], int t_right[5], int components[5][5], int counter) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        t_data[i] = obj[i];
    }
    if (isOperator(obj[0]) == 1) {
        buildTree(components[counter], trace, t_right, t_left, t_right, components, counter - 1);
    } else {
        for (i = 0; i < 5; i = i + 1) {
            t_right[i] = 0;
        }
    }
    if (isOperator(obj[0]) == 1) {
        buildTree(components[counter], trace, t_left, t_left, t_right, components, counter - 1);
    } else {
        for (i = 0; i < 5; i = i + 1) {
            t_left[i] = 0;
        }
    }
    if (trace[0] != 0) {
        inorder(t_data, t_left, t_right);
    }
    return;
}

int getNextString(int components[5][5], int counter) {
    if (counter < 0) {
        return 0;
    }
    return counter;
}

void main() {
    int t_data[5];
    int t_left[5];
    int t_right[5];
    int components[5][5];
    int counter;
    int str[5];
    int trace[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        t_data[i] = 0;
        t_left[i] = 0;
        t_right[i] = 0;
        str[i] = 0;
        trace[i] = 0;
    }
    counter = 0;
    buildStack(str, components, counter);
    if (checkRPN(components, counter) == 0) {
        return;
    }
    counter = getNextString(components, counter);
    buildTree(components[counter], trace, t_data, t_left, t_right, components, counter);
    inorder(t_data, t_left, t_right);
    return;
}
