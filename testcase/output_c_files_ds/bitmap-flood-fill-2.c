int FillContour(int iXseed, int iYseed, int color, int _data[1], int iXmax, int iYmax, int iInterior, int iJulia) {
    int iX;
    int iY;
    int iXmidLocal;
    int iXminLocal;
    int iXmaxLocal;
    int i;
    int iSide;
    int j;
    int k;

    iY = iYseed;
    iXmidLocal = iXseed;
    for (;;) {
        iX = iXmidLocal;
        i = (iX + (iYmax - iY - 1) * iXmax);
        while (_data[i] == iInterior) {
            _data[i] = color;
            iX = iX + 1;
            i = (iX + (iYmax - iY - 1) * iXmax);
        }
        iXmaxLocal = iX - 1;
        iX = iXmidLocal - 1;
        i = (iX + (iYmax - iY - 1) * iXmax);
        while (_data[i] == iInterior) {
            _data[i] = color;
            iX = iX - 1;
            i = (iX + (iYmax - iY - 1) * iXmax);
        }
        iXminLocal = iX + 1;
        iY = iY + 1;
        iXmidLocal = iXminLocal + (iXmaxLocal - iXminLocal) / 2;
        i = (iXmidLocal + (iYmax - iY - 1) * iXmax);
        if (_data[i] == iJulia) {
            break;
        }
        if (iY >= iYmax) {
            break;
        }
    }

    iXmidLocal = iXseed;
    iY = iYseed - 1;
    for (;;) {
        iX = iXmidLocal;
        i = (iX + (iYmax - iY - 1) * iXmax);
        while (_data[i] == iInterior) {
            _data[i] = color;
            iX = iX + 1;
            i = (iX + (iYmax - iY - 1) * iXmax);
        }
        iXmaxLocal = iX - 1;
        iX = iXmidLocal - 1;
        i = (iX + (iYmax - iY - 1) * iXmax);
        while (_data[i] == iInterior) {
            _data[i] = color;
            iX = iX - 1;
            i = (iX + (iYmax - iY - 1) * iXmax);
        }
        iXminLocal = iX + 1;
        iY = iY - 1;
        iXmidLocal = iXminLocal + (iXmaxLocal - iXminLocal) / 2;
        i = (iXmidLocal + (iYmax - iY - 1) * iXmax);
        if (_data[i] == iJulia) {
            break;
        }
        if (iY <= 0) {
            break;
        }
    }

    iSide = iXmax / 500;
    for (j = iYseed - iSide; j <= iYseed + iSide; j = j + 1) {
        for (k = iXseed - iSide; k <= iXseed + iSide; k = k + 1) {
            i = (k + (iYmax - j - 1) * iXmax);
            _data[i] = 10;
        }
    }
    return 0;
}
