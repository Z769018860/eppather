int queue_operations(int v1, int v2, int v3, int v4, int v5)
{
    int fifo_list[5][2];
    int val[5];
    int result[5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        val[i] = 0;
        result[i] = 0;
        for (j = 0; j < 2; j = j + 1) {
            fifo_list[i][j] = 0;
        }
    }
    
    val[0] = v1;
    fifo_list[0][0] = val[0];
    fifo_list[0][1] = 0;
    
    val[1] = v2;
    fifo_list[1][0] = val[1];
    fifo_list[1][1] = 1;
    
    val[2] = v3;
    fifo_list[2][0] = val[2];
    fifo_list[2][1] = 2;
    
    val[3] = v4;
    fifo_list[3][0] = val[3];
    fifo_list[3][1] = 3;
    
    val[4] = v5;
    fifo_list[4][0] = val[4];
    fifo_list[4][1] = 4;
    
    for (i = 0; i < 5; i = i + 1) {
        if (fifo_list[i][0] != 0) {
            result[i] = fifo_list[i][0];
            fifo_list[i][0] = 0;
            fifo_list[i][1] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (fifo_list[i][0] == 0) {
            result[0] = 1;
        } else {
            result[0] = 0;
        }
    }
    
    return;
}
