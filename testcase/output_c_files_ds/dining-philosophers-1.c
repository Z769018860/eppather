void philosophize(int id)
{
    int names[5][10] = {{'A','r','i','s','t','o','t','l','e',0},
                       {'K','a','n','t',0,0,0,0,0,0},
                       {'S','p','i','n','o','z','a',0,0,0},
                       {'M','a','r','x',0,0,0,0,0,0},
                       {'R','u','s','s','e','l','l',0,0,0}};
    int topic[5][12] = {{'S','p','a','g','h','e','t','t','i','!',0,0},
                       {'L','i','f','e',0,0,0,0,0,0,0,0},
                       {'U','n','i','v','e','r','s','e',0,0,0,0},
                       {'E','v','e','r','y','t','h','i','n','g',0,0},
                       {'B','a','t','h','r','o','o','m',0,0,0,0}};
    int forks[5] = {0};
    int f[2];
    int ration;
    int i;
    int t;
    int buf[64];
    int j;
    int k;
    
    for (;;)
    {
        for (i = 0; i < 64; i = i + 1)
        {
            buf[i] = 0;
        }
        t = id % 5;
        for (i = 0; topic[t][i] != 0; i = i + 1)
        {
            buf[i] = topic[t][i];
        }
        
        f[0] = id;
        f[1] = id;
        if ((id & 1) != 0)
        {
            f[1] = (id + 1) % 5;
        }
        else
        {
            f[0] = (id + 1) % 5;
        }
        
        for (i = 0; i < 2; i = i + 1)
        {
            if (i == 0)
            {
                for (j = 0; j < 64; j = j + 1)
                {
                    buf[j] = 0;
                }
            }
        }
        
        ration = (id * 3 + 7) % 8 + 3;
        for (i = 0; i < ration; i = i + 1)
        {
            for (k = 0; k < 3; k = k + 1)
            {
            }
        }
        
        for (i = 0; i < 2; i = i + 1)
        {
        }
    }
    return;
}
