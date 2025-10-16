void show_set(int x, int name[10])
{
    int i;
    int temp;
    for (i = 0; i < 32; i = i + 1)
    {
        temp = 1;
        temp = temp << i;
        if (x & temp)
        {
            name[i] = 1;
        }
        else
        {
            name[i] = 0;
        }
    }
    return;
}

void set_operations(int a, int b, int result[7][10])
{
    int i;
    int temp_a[10];
    int temp_b[10];
    int temp_c[10];
    int temp_union[10];
    int temp_common[10];
    int temp_a_minus_b[10];
    int temp_b_minus_a[10];
    int temp_subset_b_a[10];
    int temp_subset_c_a[10];
    int temp_union_minus_common[10];
    int temp_union_diff[10];
    
    for (i = 0; i < 10; i = i + 1)
    {
        temp_a[i] = 0;
        temp_b[i] = 0;
        temp_c[i] = 0;
        temp_union[i] = 0;
        temp_common[i] = 0;
        temp_a_minus_b[i] = 0;
        temp_b_minus_a[i] = 0;
        temp_subset_b_a[i] = 0;
        temp_subset_c_a[i] = 0;
        temp_union_minus_common[i] = 0;
        temp_union_diff[i] = 0;
    }
    
    show_set(a, temp_a);
    show_set(b, temp_b);
    
    for (i = 0; i < 10; i = i + 1)
    {
        temp_union[i] = temp_a[i] | temp_b[i];
        temp_common[i] = temp_a[i] & temp_b[i];
        temp_a_minus_b[i] = temp_a[i] & (~temp_b[i]);
        temp_b_minus_a[i] = temp_b[i] & (~temp_a[i]);
        temp_subset_b_a[i] = !(temp_b[i] & (~temp_a[i]));
        temp_subset_c_a[i] = !(temp_common[i] & (~temp_a[i]));
        temp_union_minus_common[i] = (temp_union[i] & (~temp_common[i]));
        temp_union_diff[i] = (temp_a_minus_b[i] | temp_b_minus_a[i]);
    }
    
    for (i = 0; i < 10; i = i + 1)
    {
        result[0][i] = temp_a[i];
        result[1][i] = temp_b[i];
        result[2][i] = temp_union[i];
        result[3][i] = temp_common[i];
        result[4][i] = temp_a_minus_b[i];
        result[5][i] = temp_b_minus_a[i];
        result[6][i] = (temp_union_minus_common[i] == temp_union_diff[i]);
    }
    return;
}
