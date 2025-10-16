int map[25];
int w;
int ww;

void make_map(int p, int rand_max)
{
    int i;
    int thresh = rand_max * p;
    ww = w * w;
    for (i = 0; i < 25; i = i + 1)
    {
        if (i < ww)
        {
            int rand_val = 0;
            if (rand_val < thresh)
            {
                map[i] = -1;
            }
            else
            {
                map[i] = 0;
            }
        }
        else
        {
            map[i] = 0;
        }
    }
}

void show_cluster(void)
{
    int i;
    int j;
    int s[1];
    s[0] = 0;
    char alpha[54] = "+.ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int ALEN = 51;
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < w)
        {
            for (j = 0; j < 5; j = j + 1)
            {
                if (j < w)
                {
                    if (map[s[0]] < ALEN)
                    {
                        int temp = 1 + map[s[0]];
                        char c = alpha[temp];
                    }
                    else
                    {
                        char c = '?';
                    }
                    s[0] = s[0] + 1;
                }
            }
            char c = '\n';
        }
    }
}

void recur(int x, int v)
{
    if (x >= 0 && x < ww && map[x] == -1)
    {
        map[x] = v;
        recur(x - w, v);
        recur(x - 1, v);
        recur(x + 1, v);
        recur(x + w, v);
    }
    return;
}

int count_clusters(void)
{
    int i;
    int cls;
    cls = 0;
    for (i = 0; i < 25; i = i + 1)
    {
        if (i < ww)
        {
            if (map[i] != -1)
            {
                continue;
            }
            cls = cls + 1;
            recur(i, cls);
        }
    }
    return cls;
}

int tests(int n, int p, int rand_max)
{
    int i;
    int k;
    k = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < n)
        {
            make_map(p, rand_max);
            k = k + count_clusters() / ww;
        }
    }
    return k / n;
}

void main_func(void)
{
    w = 15;
    make_map(5, 10);
    count_clusters();
    show_cluster();
    for (w = 4; w <= 16384; w = w * 4)
    {
        tests(5, 5, 10);
    }
    return;
}
