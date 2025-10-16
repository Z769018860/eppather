int next_perm(int size, int nums[5])
{
    int k[5];
    int l[5];
    int tmp[5];
    int n1;
    int n2;
    
    n1 = size - 2;
    for (k[0] = n1; k[0] >= 0; k[0] = k[0] - 1)
    {
        if (nums[k[0]] < nums[k[0] + 1])
        {
            break;
        }
    }
    if (k[0] < 0)
    {
        return 0;
    }
    
    n2 = size - 1;
    for (l[0] = n2; l[0] >= 0; l[0] = l[0] - 1)
    {
        if (nums[l[0]] > nums[k[0]])
        {
            break;
        }
    }
    tmp[0] = nums[k[0]];
    nums[k[0]] = nums[l[0]];
    nums[l[0]] = tmp[0];
    
    for (l[0] = size - 1, k[0] = k[0] + 1; k[0] < l[0]; k[0] = k[0] + 1, l[0] = l[0] - 1)
    {
        tmp[0] = nums[k[0]];
        nums[k[0]] = nums[l[0]];
        nums[l[0]] = tmp[0];
    }
    
    return 1;
}

void make_part(int n, int sizes[5])
{
    int x[5];
    int i[5];
    int j[5];
    int ptr[5];
    int len[5];
    int n3;
    int n4;
    
    len[0] = 0;
    ptr[0] = 0;
    for (i[0] = 0; i[0] < n; i[0] = i[0] + 1)
    {
        n3 = sizes[i[0]];
        for (j[0] = 0; j[0] < n3; j[0] = j[0] + 1)
        {
            x[ptr[0]] = i[0];
            ptr[0] = ptr[0] + 1;
            len[0] = len[0] + 1;
        }
    }
    
    do
    {
        for (i[0] = 0; i[0] < n; i[0] = i[0] + 1)
        {
            for (j[0] = 0; j[0] < len[0]; j[0] = j[0] + 1)
            {
                if (x[j[0]] == i[0])
                {
                }
            }
        }
    } while (next_perm(len[0], x));
    
    return;
}
