void demo_binary_op(int operator[3][3], int name[5]) {
    int operand1[5];
    int operand2[5];
    int tritNot[3] = {2, 1, 0};
    int tritAnd[3][3] = {{0, 1, 2}, {1, 1, 2}, {2, 2, 2}};
    int tritOr[3][3] = {{0, 0, 0}, {0, 1, 1}, {0, 1, 2}};
    int tritThen[3][3] = {{0, 1, 2}, {0, 1, 1}, {0, 0, 0}};
    int tritEquiv[3][3] = {{0, 1, 2}, {1, 1, 1}, {2, 1, 0}};
    int tritString[3][5] = {{84, 0, 0, 0, 0}, {63, 0, 0, 0, 0}, {70, 0, 0, 0, 0}};

    for (operand1[0] = 0; operand1[0] < 3; operand1[0] = operand1[0] + 1) {
        for (operand2[0] = 0; operand2[0] < 3; operand2[0] = operand2[0] + 1) {
            int temp[5];
            temp[0] = operator[operand1[0]][operand2[0]];
        }
    }

    for (operand1[0] = 0; operand1[0] < 3; operand1[0] = operand1[0] + 1) {
        int temp[5];
        temp[0] = tritNot[operand1[0]];
    }

    return;
}
