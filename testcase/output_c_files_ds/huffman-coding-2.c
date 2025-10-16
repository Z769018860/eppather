int pool_left[256];
int pool_right[256];
int pool_freq[256];
char pool_c[256];
int qqq_left[255];
int qqq_right[255];
int qqq_freq[255];
char qqq_c[255];
int qqq_index[255];
int n_nodes = 0;
int qend = 1;
char code_buf[128][1024];
char buf[1024];

int new_node(int freq, char c, int a, int b)
{
    int n = n_nodes;
    n_nodes = n_nodes + 1;
    if (freq != 0)
    {
        pool_c[n] = c;
        pool_freq[n] = freq;
    }
    else
    {
        pool_left[n] = a;
        pool_right[n] = b;
        pool_freq[n] = pool_freq[a] + pool_freq[b];
    }
    return n;
}

void qinsert(int n)
{
    int j;
    int i = qend;
    qend = qend + 1;
    while (1)
    {
        j = i / 2;
        if (j == 0)
        {
            break;
        }
        if (qqq_freq[j] <= pool_freq[n])
        {
            break;
        }
        qqq_left[i] = qqq_left[j];
        qqq_right[i] = qqq_right[j];
        qqq_freq[i] = qqq_freq[j];
        qqq_c[i] = qqq_c[j];
        qqq_index[i] = qqq_index[j];
        i = j;
    }
    qqq_left[i] = pool_left[n];
    qqq_right[i] = pool_right[n];
    qqq_freq[i] = pool_freq[n];
    qqq_c[i] = pool_c[n];
    qqq_index[i] = n;
}

int qremove()
{
    int i;
    int l;
    int n = qqq_index[1];
    if (qend < 2)
    {
        return 0;
    }
    qend = qend - 1;
    i = 1;
    while (1)
    {
        l = i * 2;
        if (l >= qend)
        {
            break;
        }
        if (l + 1 < qend && qqq_freq[l + 1] < qqq_freq[l])
        {
            l = l + 1;
        }
        qqq_left[i] = qqq_left[l];
        qqq_right[i] = qqq_right[l];
        qqq_freq[i] = qqq_freq[l];
        qqq_c[i] = qqq_c[l];
        qqq_index[i] = qqq_index[l];
        i = l;
    }
    qqq_left[i] = qqq_left[qend];
    qqq_right[i] = qqq_right[qend];
    qqq_freq[i] = qqq_freq[qend];
    qqq_c[i] = qqq_c[qend];
    qqq_index[i] = qqq_index[qend];
    return n;
}

void build_code(int n, char s[], int len)
{
    static int out_pos = 0;
    if (pool_c[n] != 0)
    {
        s[len] = 0;
        int k;
        for (k = 0; k < len + 1; k = k + 1)
        {
            code_buf[pool_c[n]][k] = s[k];
        }
        out_pos = out_pos + len + 1;
        return;
    }
    s[len] = '0';
    build_code(pool_left[n], s, len + 1);
    s[len] = '1';
    build_code(pool_right[n], s, len + 1);
}

void init(const char s[])
{
    int freq[128] = {0};
    char c[16];
    int i = 0;
    while (s[i] != 0)
    {
        freq[(int)s[i]] = freq[(int)s[i]] + 1;
        i = i + 1;
    }
    for (i = 0; i < 128; i = i + 1)
    {
        if (freq[i] != 0)
        {
            int node = new_node(freq[i], (char)i, 0, 0);
            qinsert(node);
        }
    }
    while (qend > 2)
    {
        int a = qremove();
        int b = qremove();
        int node = new_node(0, 0, a, b);
        qinsert(node);
    }
    build_code(qqq_index[1], c, 0);
}

void encode(const char s[], char out[])
{
    int i = 0;
    int out_pos = 0;
    while (s[i] != 0)
    {
        int k = 0;
        while (code_buf[(int)s[i]][k] != 0)
        {
            out[out_pos] = code_buf[(int)s[i]][k];
            out_pos = out_pos + 1;
            k = k + 1;
        }
        i = i + 1;
    }
    out[out_pos] = 0;
}

void decode(const char s[], int t)
{
    int n = t;
    int i = 0;
    while (s[i] != 0)
    {
        if (s[i] == '0')
        {
            n = pool_left[n];
        }
        else
        {
            n = pool_right[n];
        }
        i = i + 1;
        if (pool_c[n] != 0)
        {
            n = t;
        }
    }
    return;
}
