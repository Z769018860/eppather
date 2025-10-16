int FillContour(int iXseed, int iYseed, int color, int _data[5], int iXmax, int iYmax, int iInterior, int iJulia) {
    int iX[5];
    int iY[5];
    int iXmidLocal[5];
    int iXminLocal[5];
    int iXmaxLocal[5];
    int i[5];
    int iSide[5];
    
    iY[0] = iYseed;
    iXmidLocal[0] = iXseed;
    
    for (iY[0] = iYseed; iY[0] < iYmax; iY[0] = iY[0] + 1) {
        iX[0] = iXmidLocal[0];
        i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        
        while (_data[i[0]] == iInterior) {
            _data[i[0]] = color;
            iX[0] = iX[0] + 1;
            i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        }
        iXmaxLocal[0] = iX[0] - 1;
        
        iX[0] = iXmidLocal[0] - 1;
        i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        while (_data[i[0]] == iInterior) {
            _data[i[0]] = color;
            iX[0] = iX[0] - 1;
            i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        }
        iXminLocal[0] = iX[0] + 1;
        
        iY[0] = iY[0] + 1;
        iXmidLocal[0] = iXminLocal[0] + (iXmaxLocal[0] - iXminLocal[0]) / 2;
        i[0] = (iXmidLocal[0] + (iYmax - iY[0] - 1) * iXmax);
        if (_data[i[0]] == iJulia) {
            break;
        }
    }
    
    iXmidLocal[0] = iXseed;
    iY[0] = iYseed - 1;
    
    for (iY[0] = iYseed - 1; iY[0] > 0; iY[0] = iY[0] - 1) {
        iX[0] = iXmidLocal[0];
        i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        
        while (_data[i[0]] == iInterior) {
            _data[i[0]] = color;
            iX[0] = iX[0] + 1;
            i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        }
        iXmaxLocal[0] = iX[0] - 1;
        
        iX[0] = iXmidLocal[0] - 1;
        i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        while (_data[i[0]] == iInterior) {
            _data[i[0]] = color;
            iX[0] = iX[0] - 1;
            i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
        }
        iXminLocal[0] = iX[0] + 1;
        
        iY[0] = iY[0] - 1;
        iXmidLocal[0] = iXminLocal[0] + (iXmaxLocal[0] - iXminLocal[0]) / 2;
        i[0] = (iXmidLocal[0] + (iYmax - iY[0] - 1) * iXmax);
        if (_data[i[0]] == iJulia) {
            break;
        }
    }
    
    iSide[0] = iXmax / 500;
    for (iY[0] = iYseed - iSide[0]; iY[0] <= iYseed + iSide[0]; iY[0] = iY[0] + 1) {
        for (iX[0] = iXseed - iSide[0]; iX[0] <= iXseed + iSide[0]; iX[0] = iX[0] + 1) {
            i[0] = (iX[0] + (iYmax - iY[0] - 1) * iXmax);
            _data[i[0]] = 10;
        }
    }
    
    return 0;
}
