void mandelbrot(int iXmax, int iYmax, int IterationMax, int MaxColorComponentValue) {
    int iX[5];
    int iY[5];
    double Cx[5];
    double Cy[5];
    double PixelWidth[5];
    double PixelHeight[5];
    double Zx[5];
    double Zy[5];
    double Zx2[5];
    double Zy2[5];
    int Iteration[5];
    double CxMin[5];
    double CxMax[5];
    double CyMin[5];
    double CyMax[5];
    double EscapeRadius[5];
    double ER2[5];
    unsigned char color[3];
    
    CxMin[0] = -2.5;
    CxMax[0] = 1.5;
    CyMin[0] = -2.0;
    CyMax[0] = 2.0;
    PixelWidth[0] = (CxMax[0] - CxMin[0]) / iXmax;
    PixelHeight[0] = (CyMax[0] - CyMin[0]) / iYmax;
    EscapeRadius[0] = 2;
    ER2[0] = EscapeRadius[0] * EscapeRadius[0];
    
    for (iY[0] = 0; iY[0] < iYmax; iY[0] = iY[0] + 1) {
        Cy[0] = CyMin[0] + iY[0] * PixelHeight[0];
        if (Cy[0] < 0) {
            if (-Cy[0] < PixelHeight[0] / 2) {
                Cy[0] = 0.0;
            }
        } else {
            if (Cy[0] < PixelHeight[0] / 2) {
                Cy[0] = 0.0;
            }
        }
        for (iX[0] = 0; iX[0] < iXmax; iX[0] = iX[0] + 1) {
            Cx[0] = CxMin[0] + iX[0] * PixelWidth[0];
            Zx[0] = 0.0;
            Zy[0] = 0.0;
            Zx2[0] = Zx[0] * Zx[0];
            Zy2[0] = Zy[0] * Zy[0];
            for (Iteration[0] = 0; Iteration[0] < IterationMax && (Zx2[0] + Zy2[0]) < ER2[0]; Iteration[0] = Iteration[0] + 1) {
                Zy[0] = 2 * Zx[0] * Zy[0] + Cy[0];
                Zx[0] = Zx2[0] - Zy2[0] + Cx[0];
                Zx2[0] = Zx[0] * Zx[0];
                Zy2[0] = Zy[0] * Zy[0];
            }
            if (Iteration[0] == IterationMax) {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            } else {
                color[0] = MaxColorComponentValue;
                color[1] = MaxColorComponentValue;
                color[2] = MaxColorComponentValue;
            }
        }
    }
    return;
}
