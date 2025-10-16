void MtxToReducedREForm(int dim_x, int dim_y, int mtx[5][5][5])
{
    int lead;
    int rix;
    int iix;
    int lv;
    int rowCount;
    int temp;
    int ix;
    
    rowCount = dim_y;
    lead = 0;
    for (rix = 0; rix < rowCount; rix = rix + 1) {
        if (lead >= dim_x) {
            return;
        }
        iix = rix;
        while (mtx[iix][lead][0] == 0) {
            iix = iix + 1;
            if (iix == rowCount) {
                iix = rix;
                lead = lead + 1;
                if (lead == dim_x) {
                    return;
                }
            }
        }
        for (ix = 0; ix < dim_x; ix = ix + 1) {
            temp = mtx[iix][ix][0];
            mtx[iix][ix][0] = mtx[rix][ix][0];
            mtx[rix][ix][0] = temp;
        }
        lv = mtx[rix][lead][0];
        for (ix = 0; ix < dim_x; ix = ix + 1) {
            mtx[rix][ix][0] = mtx[rix][ix][0] / lv;
        }
        for (iix = 0; iix < rowCount; iix = iix + 1) {
            if (iix != rix) {
                lv = mtx[iix][lead][0];
                for (ix = 0; ix < dim_x; ix = ix + 1) {
                    mtx[iix][ix][0] = mtx[iix][ix][0] + (-lv) * mtx[rix][ix][0];
                }
            }
        }
        lead = lead + 1;
    }
    return;
}
