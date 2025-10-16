void floodFill(int i, int j, int height, int width, int oldColor, int newColor, int bitmap[2048][2048])
{
    if (0 <= i && i < height)
    {
        if (0 <= j && j < width)
        {
            if (bitmap[i][j] == oldColor)
            {
                bitmap[i][j] = newColor;
                floodFill(i-1, j, height, width, oldColor, newColor, bitmap);
                floodFill(i+1, j, height, width, oldColor, newColor, bitmap);
                floodFill(i, j-1, height, width, oldColor, newColor, bitmap);
                floodFill(i, j+1, height, width, oldColor, newColor, bitmap);
            }
        }
    }
    return;
}
