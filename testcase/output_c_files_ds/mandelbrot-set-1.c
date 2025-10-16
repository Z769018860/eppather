void mandelbrot() {
    int iX;
    int iY;
    int iXmax = 800;
    int iYmax = 800;
    double Cx;
    double Cy;
    double CxMin = -2.5;
    double CxMax = 1.5;
    double CyMin = -2.0;
    double CyMax = 2.0;
    double PixelWidth = (CxMax - CxMin) / iXmax;
    double PixelHeight = (CyMax - CyMin) / iYmax;
    int MaxColorComponentValue = 255;
    unsigned char color[3];
    double Zx;
    double Zy;
    double Zx2;
    double Zy2;
    int Iteration;
    int IterationMax = 200;
    double EscapeRadius = 2;
    double ER2 = EscapeRadius * EscapeRadius;

    for (iY = 0; iY < iYmax; iY = iY + 1) {
        Cy = CyMin + iY * PixelHeight;
        if (Cy < 0) {
            if (-Cy < PixelHeight / 2) {
                Cy = 0.0;
            }
        } else {
            if (Cy < PixelHeight / 2) {
                Cy = 0.0;
            }
        }
        for (iX = 0; iX < iXmax; iX = iX + 1) {
            Cx = CxMin + iX * PixelWidth;
            Zx = 0.0;
            Zy = 0.0;
            Zx2 = Zx * Zx;
            Zy2 = Zy * Zy;
            Iteration = 0;
            for (; Iteration < IterationMax && (Zx2 + Zy2) < ER2; Iteration = Iteration + 1) {
                Zy = 2 * Zx * Zy + Cy;
                Zx = Zx2 - Zy2 + Cx;
                Zx2 = Zx * Zx;
                Zy2 = Zy * Zy;
            }
            if (Iteration == IterationMax) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            } else {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
        }
    }
    return;
}
