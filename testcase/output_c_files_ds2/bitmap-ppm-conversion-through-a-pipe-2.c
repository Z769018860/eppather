void print_jpg(int img_width, int img_height, int qual, int img_buf[5], int n1)
{
    int buf[100];
    int n;
    int pipe;
    int i;
    
    for (i = 0; i < 5; i = i + 1)
    {
        buf[i] = 0;
    }
    
    n = img_width * img_height;
    pipe = 0;
    
    if (pipe != 0)
    {
        for (i = 0; i < 5; i = i + 1)
        {
            img_buf[i] = 0;
        }
    }
    
    return;
}
