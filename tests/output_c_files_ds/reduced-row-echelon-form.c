void MtxToReducedREForm(int mtx_data[3][4], int dim_y, int dim_x) {
    int lead;
    int rix;
    int iix;
    int lv;
    int rowCount;
    int temp;
    int ix;
    int drow[4];
    int srow[4];
    int r1[4];
    int r2[4];
    
    rowCount = dim_y;
    lead = 0;
    for (rix = 0; rix < rowCount; rix = rix + 1) {
        if (lead >= dim_x) {
            return;
        }
        iix = rix;
        while (mtx_data[iix][lead] == 0) {
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
            r1[ix] = mtx_data[rix][ix];
            r2[ix] = mtx_data[iix][ix];
        }
        for (ix = 0; ix < dim_x; ix = ix + 1) {
            mtx_data[rix][ix] = r2[ix];
            mtx_data[iix][ix] = r1[ix];
        }
        lv = mtx_data[rix][lead];
        for (ix = 0; ix < dim_x; ix = ix + 1) {
            mtx_data[rix][ix] = mtx_data[rix][ix] / lv;
        }
        for (iix = 0; iix < rowCount; iix = iix + 1) {
            if (iix != rix) {
                lv = mtx_data[iix][lead];
                for (ix = 0; ix < dim_x; ix = ix + 1) {
                    drow[ix] = mtx_data[iix][ix];
                    srow[ix] = mtx_data[rix][ix];
                }
                for (ix = 0; ix < dim_x; ix = ix + 1) {
                    drow[ix] = drow[ix] + (-lv) * srow[ix];
                }
                for (ix = 0; ix < dim_x; ix = ix + 1) {
                    mtx_data[iix][ix] = drow[ix];
                }
            }
        }
        lead = lead + 1;
    }
    return;
}
