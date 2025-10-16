int p(char *t)
{
    char y[] = "#:ottle/ of:eer_ a_Go<o5st>y\x20some6_Take8;down4pa=1rou7_17 _<h;_ m?_nd_ on_085wall_ b_e _ t_ss it_?4bu_ore_9, \060.@, 9$";
    char *d[16];
    int b = 99;
    int u = 1;
    char *s = t;
    int c;
    
    for (c = 0; c < 16; c = c + 1)
    {
        d[c] = y;
    }
    
    if (t == 0)
    {
        s = d[0];
        for (c = 0; c < 15; c = c + 1)
        {
            char *temp = s;
            while (*temp != '_' && *temp != 0)
            {
                temp = temp + 1;
            }
            d[c + 1] = temp;
            *temp = 0;
            d[c] = s;
            s = temp + 1;
        }
        t = s;
    }
    
    s = t;
    for (; *s != 0; s = s + 1)
    {
        c = *s;
        if (c != 0)
        {
            if ((((c ^ 48) & ~0xf) && (c ^ 48)))
            {
                if (c == '$')
                {
                    c = 0;
                    if (b - 99)
                    {
                        p(".\n");
                    }
                    else
                    {
                        p(".");
                    }
                    if (b - 99)
                    {
                        p(t);
                    }
                    else
                    {
                        p("");
                    }
                }
                else if (c == '@')
                {
                    c = 0;
                    if (c)
                    {
                        p(d[!!b + 2]);
                    }
                    b = b - 1;
                }
                else if (c == '/')
                {
                    c = 0;
                    if (c)
                    {
                        if (b ^ 1)
                        {
                            p("s");
                        }
                        else
                        {
                            p("");
                        }
                    }
                }
                else if (c == '#')
                {
                    c = 0;
                    if (b)
                    {
                        b = b - 1;
                        p("So6");
                    }
                    else
                    {
                        b = b + 99;
                    }
                }
                else if (c == 'S')
                {
                    u = u + 1;
                    c = !(u % 3) * 32 + 78;
                }
                else if (c == '.')
                {
                    c = 0;
                    p(".");
                }
            }
            else
            {
                p(d[c]);
                c = 0;
            }
        }
    }
    return 0;
}
