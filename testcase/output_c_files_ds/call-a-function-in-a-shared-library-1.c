int myopenimage(const char *in)
{
    static int handle = 0;
    int result = handle;
    handle = handle + 1;
    return result;
}

int openimage(const char *in)
{
    int imghandle;
    int imglib_valid = 0;
    int (*extopenimage)(const char *);
    
    if (imglib_valid != 0)
    {
        imghandle = extopenimage(in);
    }
    else
    {
        imghandle = myopenimage(in);
    }
    return imghandle;
}
