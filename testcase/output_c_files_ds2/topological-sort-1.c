int parse_input(int list[5][5], int deps[5][5], int n_deps[5], int idx[5], int depth[5], char name[5][5][5])
{
    int n_items = 0;
    int i = 0;
    int parent = 0;
    int idx_val = 0;
    int s = 0;
    int e = 0;
    int word = 0;
    int we = 0;
    int j = 0;
    int found = 0;
    int k = 0;
    
    for (s = 0; s < 5; s = s + 1)
    {
        for (i = 0; i < 5; i = i + 1)
        {
            for (j = 0; j < 5; j = j + 1)
            {
                name[s][i][j] = 0;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        n_deps[i] = 0;
        idx[i] = 0;
        depth[i] = 0;
        for (j = 0; j < 5; j = j + 1)
        {
            deps[i][j] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        found = 0;
        for (j = 0; j < 5; j = j + 1)
        {
            if (name[i][0][j] != 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            idx_val = n_items;
            n_items = n_items + 1;
            idx[idx_val] = idx_val;
            for (j = 0; j < 5; j = j + 1)
            {
                name[idx_val][0][j] = 0;
            }
        }
        else
        {
            idx_val = j;
        }
        
        if (i == 0)
        {
            parent = idx_val;
        }
        else
        {
            if (idx_val != parent)
            {
                deps[parent][n_deps[parent]] = idx_val;
                n_deps[parent] = n_deps[parent] + 1;
            }
        }
    }
    
    return n_items;
}

int get_depth(int list[5][5], int deps[5][5], int n_deps[5], int idx[5], int depth[5], int current_idx, int bad)
{
    int max = 0;
    int i = 0;
    int t = 0;
    
    if (n_deps[current_idx] == 0)
    {
        depth[current_idx] = 1;
        return 1;
    }
    
    t = depth[current_idx];
    if (t < 0)
    {
        return t;
    }
    
    depth[current_idx] = bad;
    for (i = 0; i < n_deps[current_idx]; i = i + 1)
    {
        t = get_depth(list, deps, n_deps, idx, depth, deps[current_idx][i], bad);
        if (t < 0)
        {
            max = t;
            break;
        }
        if (max < t + 1)
        {
            max = t + 1;
        }
    }
    depth[current_idx] = max;
    return max;
}

void main()
{
    int list[5][5];
    int deps[5][5];
    int n_deps[5];
    int idx[5];
    int depth[5];
    char name[5][5][5];
    int i = 0;
    int j = 0;
    int n = 0;
    int bad = -1;
    int max = 0;
    int min = 0;
    
    n = parse_input(list, deps, n_deps, idx, depth, name);
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (depth[i] == 0)
        {
            if (get_depth(list, deps, n_deps, idx, depth, i, bad) < 0)
            {
                bad = bad - 1;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (depth[i] > max)
        {
            max = depth[i];
        }
        if (depth[i] < min)
        {
            min = depth[i];
        }
    }
    
    return;
}
