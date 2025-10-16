int get_histogram_median(int im_buf[], int im_width, int im_height)
{
    int histogram[256];
    int x;
    int y;
    int i;
    int sum;
    int median;
    
    for (i = 0; i < 256; i = i + 1)
    {
        histogram[i] = 0;
    }
    
    for (y = 0; y < im_height; y = y + 1)
    {
        for (x = 0; x < im_width; x = x + 1)
        {
            int pixel = im_buf[y * im_width + x];
            histogram[pixel] = histogram[pixel] + 1;
        }
    }
    
    sum = 0;
    for (i = 0; i < 256; i = i + 1)
    {
        sum = sum + histogram[i];
        if (sum * 2 > im_width * im_height)
        {
            median = i;
            break;
        }
    }
    
    return median;
}
