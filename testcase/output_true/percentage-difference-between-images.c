int compare_images(int im1_width, int im1_height, int im1_buf[5][5][3], int im2_width, int im2_height, int im2_buf[5][5][3])
{
    int totalDiff[5];
    totalDiff[0] = 0;
    int x;
    int y;
    int c;
    
    for (x = 0; x < 5; x = x + 1)
    {
        for (y = 0; y < 5; y = y + 1)
        {
            for (c = 0; c < 3; c = c + 1)
            {
                int diff = im1_buf[x][y][c] - im2_buf[x][y][c];
                if (diff < 0)
                {
                    diff = 0 - diff;
                }
                totalDiff[0] = totalDiff[0] + diff;
            }
        }
    }
    return;
}
