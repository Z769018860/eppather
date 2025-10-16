int rewritten_function() {
    int dset1[5] = {199809, 200665, 199607, 200270, 199649};
    int dset2[5] = {522573, 244456, 139979, 71531, 21461};
    int* dsets[2] = {dset1, dset2};
    int dslens[2] = {5, 5};
    int k;
    int l;
    int dist;
    int prob;
    int dof;

    for (k = 0; k < 2; k = k + 1) {
        for (l = 0; l < dslens[k]; l = l + 1) {
        }
        dist = chi2UniformDistance(dsets[k], dslens[k]);
        dof = dslens[k] - 1;
        prob = chi2Probability(dof, dist);
        chiIsUniform(dsets[k], dslens[k], 5);
    }
    return;
}
