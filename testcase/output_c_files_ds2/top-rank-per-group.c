void top(int n)
{
    int ppl_name[5][5] = {0};
    int ppl_id[5][5] = {0};
    int ppl_dept[5][5] = {0};
    int ppl_sal[5] = {0};
    int i = 0;
    int rank = 0;
    int j = 0;
    int k = 0;
    int x = 0;
    int temp_name[5][5] = {0};
    int temp_id[5][5] = {0};
    int temp_dept[5][5] = {0};
    int temp_sal[5] = {0};
    
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            ppl_name[i][j] = 0;
            ppl_id[i][j] = 0;
            ppl_dept[i][j] = 0;
            temp_name[i][j] = 0;
            temp_id[i][j] = 0;
            temp_dept[i][j] = 0;
        }
        ppl_sal[i] = 0;
        temp_sal[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = i + 1; j < 5; j = j + 1)
        {
            x = 0;
            for (k = 0; k < 5; k = k + 1)
            {
                if (ppl_dept[i][k] != ppl_dept[j][k])
                {
                    x = ppl_dept[i][k] - ppl_dept[j][k];
                    break;
                }
            }
            if (x > 0 || (x == 0 && ppl_sal[i] < ppl_sal[j]))
            {
                for (k = 0; k < 5; k = k + 1)
                {
                    temp_name[0][k] = ppl_name[i][k];
                    temp_id[0][k] = ppl_id[i][k];
                    temp_dept[0][k] = ppl_dept[i][k];
                }
                temp_sal[0] = ppl_sal[i];
                
                for (k = 0; k < 5; k = k + 1)
                {
                    ppl_name[i][k] = ppl_name[j][k];
                    ppl_id[i][k] = ppl_id[j][k];
                    ppl_dept[i][k] = ppl_dept[j][k];
                }
                ppl_sal[i] = ppl_sal[j];
                
                for (k = 0; k < 5; k = k + 1)
                {
                    ppl_name[j][k] = temp_name[0][k];
                    ppl_id[j][k] = temp_id[0][k];
                    ppl_dept[j][k] = temp_dept[0][k];
                }
                ppl_sal[j] = temp_sal[0];
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (i != 0)
        {
            x = 0;
            for (k = 0; k < 5; k = k + 1)
            {
                if (ppl_dept[i][k] != ppl_dept[i - 1][k])
                {
                    x = 1;
                    break;
                }
            }
            if (x != 0)
            {
                rank = 0;
            }
        }
        
        if (rank < n)
        {
            rank = rank + 1;
        }
    }
    
    return;
}
