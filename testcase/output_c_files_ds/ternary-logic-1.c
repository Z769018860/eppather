int tritNot[3] = {2, 1, 0};
int tritAnd[3][3] = {{0, 1, 2}, {1, 1, 2}, {2, 2, 2}};
int tritOr[3][3] = {{0, 0, 0}, {0, 1, 1}, {0, 1, 2}};
int tritThen[3][3] = {{0, 1, 2}, {0, 1, 1}, {0, 0, 0}};
int tritEquiv[3][3] = {{0, 1, 2}, {1, 1, 1}, {2, 1, 0}};

void demo_binary_op(int operator[3][3])
{
    int operand1;
    int operand2;
    int result[3][3];
    
    for (operand1 = 0; operand1 <= 2; operand1 = operand1 + 1)
    {
        for (operand2 = 0; operand2 <= 2; operand2 = operand2 + 1)
        {
            result[operand1][operand2] = operator[operand1][operand2];
        }
    }
    return;
}
