void print_names(int node[5], int next[5], int type[5], int name[5], int prop[5], int children[5], int content[5])
{
    int cur_node[5];
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        cur_node[i] = node[i];
    }
    for (i = 0; i < 5; i = i + 1)
    {
        if (cur_node[0] != 0)
        {
            if (type[0] == 1)
            {
                if (name[0] == 0)
                {
                    if (prop[0] != 0)
                    {
                        content[0] = 0;
                    }
                }
            }
            print_names(children, next, type, name, prop, children, content);
            for (i = 0; i < 5; i = i + 1)
            {
                cur_node[i] = next[i];
            }
        }
    }
    return;
}
