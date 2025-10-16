void tree_traversal(int v, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9)
{
    int node_value[5] = {v, l1, l2, l3, l4};
    int left_child[5] = {1, 2, 4, 7, 0};
    int right_child[5] = {3, 5, 0, 0, 0};
    int queue_begin[5] = {0};
    int queue_end[5] = {0};
    int queue_next[5] = {0};
    int queue_value[5] = {0};
    int visited[5] = {0};
    int i;
    int j;
    int current;
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (node_value[i] != 0)
        {
            if (left_child[i] != 0)
            {
                for (j = 0; j < 5; j = j + 1)
                {
                    if (node_value[j] == left_child[i])
                    {
                        break;
                    }
                }
            }
            if (right_child[i] != 0)
            {
                for (j = 0; j < 5; j = j + 1)
                {
                    if (node_value[j] == right_child[i])
                    {
                        break;
                    }
                }
            }
        }
    }
    
    current = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (node_value[i] != 0)
        {
            if (visited[i] == 0)
            {
                visited[i] = 1;
                if (left_child[i] != 0)
                {
                    for (j = 0; j < 5; j = j + 1)
                    {
                        if (node_value[j] == left_child[i])
                        {
                            break;
                        }
                    }
                }
                if (right_child[i] != 0)
                {
                    for (j = 0; j < 5; j = j + 1)
                    {
                        if (node_value[j] == right_child[i])
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        queue_begin[i] = 0;
        queue_end[i] = 0;
        queue_next[i] = 0;
        queue_value[i] = 0;
    }
    
    current = 0;
    queue_begin[0] = 1;
    queue_end[0] = 1;
    queue_value[0] = node_value[0];
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (queue_begin[i] != 0)
        {
            current = queue_value[i];
            if (left_child[i] != 0)
            {
                for (j = 0; j < 5; j = j + 1)
                {
                    if (node_value[j] == left_child[i])
                    {
                        break;
                    }
                }
            }
            if (right_child[i] != 0)
            {
                for (j = 0; j < 5; j = j + 1)
                {
                    if (node_value[j] == right_child[i])
                    {
                        break;
                    }
                }
            }
        }
    }
    
    return;
}
