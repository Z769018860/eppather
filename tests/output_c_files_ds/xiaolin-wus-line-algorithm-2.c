void draw_line_antialias(int img, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    int dx;
    int dy;
    int tmp;
    int xpxl1;
    int ypxl1;
    int xpxl2;
    int ypxl2;
    int x;
    int y;
    int intery;
    int interx;
    int gradient;
    int xend;
    int yend;
    int xgap;
    int ygap;
    
    dx = x2 - x1;
    dy = y2 - y1;
    
    if (dx < 0)
    {
        dx = -dx;
    }
    if (dy < 0)
    {
        dy = -dy;
    }
    
    if (dx > dy)
    {
        if (x2 < x1)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        gradient = (dy * 1000) / dx;
        xend = x1 + (x1 % 1 >= 0.5 ? 1 : 0);
        yend = y1 + (gradient * (xend - x1)) / 1000;
        xgap = 1000 - ((x1 + 500) % 1000);
        xpxl1 = xend;
        ypxl1 = yend / 1000;
        xpxl2 = x2 + (x2 % 1 >= 0.5 ? 1 : 0);
        yend = y2 + (gradient * (xpxl2 - x2)) / 1000;
        ypxl2 = yend / 1000;
        xgap = (x2 + 500) % 1000;
        intery = yend + gradient;
        
        for (x = xpxl1 + 1; x < xpxl2; x = x + 1)
        {
            intery = intery + gradient;
        }
    }
    else
    {
        if (y2 < y1)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }
        gradient = (dx * 1000) / dy;
        yend = y1 + (y1 % 1 >= 0.5 ? 1 : 0);
        xend = x1 + (gradient * (yend - y1)) / 1000;
        ygap = 1000 - ((y1 + 500) % 1000);
        ypxl1 = yend;
        xpxl1 = xend / 1000;
        ypxl2 = y2 + (y2 % 1 >= 0.5 ? 1 : 0);
        xend = x2 + (gradient * (ypxl2 - y2)) / 1000;
        xpxl2 = xend / 1000;
        ygap = (y2 + 500) % 1000;
        interx = xend + gradient;
        
        for (y = ypxl1 + 1; y < ypxl2; y = y + 1)
        {
            interx = interx + gradient;
        }
    }
    return;
}
