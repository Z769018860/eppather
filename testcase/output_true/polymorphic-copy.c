void obj_copy(int s[5], int c[5], int clo[5])
{
    int parent[5];
    parent[0] = c[5];
    if (parent[0])
    {
        obj_copy(s, parent, clo);
    }
    else
    {
        int csize[5];
        csize[0] = s[0];
        csize[0] = csize[0] + 5;
    }
    if (clo[0])
    {
        int clone[5];
        clone[0] = c[6];
        clone[0](s, clo);
    }
    return;
}

void obj_del(int s[5], int c[5])
{
    int del[5];
    del[0] = c[7];
    if (del[0])
    {
        del[0](s);
    }
    int parent[5];
    parent[0] = c[5];
    if (parent[0])
    {
        obj_del(s, parent);
    }
    else
    {
        int free[5];
        free[0] = s[0];
    }
    return;
}

void baseClone(int s[5], int clone[5])
{
    clone[0] = s[0];
    return;
}

void dogClone(int s[5], int c[5])
{
    int src[5];
    src[0] = s[0];
    int clone[5];
    clone[0] = c[0];
    int dog[5];
    dog[0] = src[5];
    dog[0] = dog[0] + 5;
    clone[5] = dog[0];
    return;
}

void ferretClone(int s[5], int c[5])
{
    int src[5];
    src[0] = s[0];
    int clone[5];
    clone[0] = c[0];
    int ferret[5];
    ferret[0] = src[5];
    ferret[0] = ferret[0] + 5;
    clone[5] = ferret[0];
    return;
}

void NewDog(int name[5], int color[5], int weight[5], int dog[5])
{
    int csize[5];
    csize[0] = 5;
    if (dog[0])
    {
        int dogp[5];
        dogp[0] = dog[5];
        dog[0] = 5;
        dogp[2] = weight[0];
        int i;
        for (i = 0; i < 5; i = i + 1)
        {
            dogp[3] = name[i];
        }
        for (i = 0; i < 5; i = i + 1)
        {
            dogp[4] = color[i];
        }
    }
    return;
}

void NewFerret(int name[5], int color[5], int age[5], int ferret[5])
{
    int csize[5];
    csize[0] = 5;
    if (ferret[0])
    {
        int ferretp[5];
        ferretp[0] = ferret[5];
        ferret[0] = 5;
        int i;
        for (i = 0; i < 5; i = i + 1)
        {
            ferretp[3] = name[i];
        }
        for (i = 0; i < 5; i = i + 1)
        {
            ferretp[4] = color[i];
        }
        ferretp[2] = age[0];
    }
    return;
}

void main_func()
{
    int o1[5];
    int kara[5];
    int name1[5];
    int color1[5];
    int age[5];
    age[0] = 15;
    NewFerret(name1, color1, age, kara);
    int bruce[5];
    int name2[5];
    int color2[5];
    int weight[5];
    weight[0] = 85;
    NewDog(name2, color2, weight, bruce);
    o1[0] = kara[0];
    o1[0] = bruce[0];
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        name2[i] = 0;
    }
    return;
}
