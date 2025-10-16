int vector_operations(int a_i, int a_j, int a_k, int b_i, int b_j, int b_k, int c_i, int c_j, int c_k, int results[7]) {
    int dot_ab;
    int cross_ab[3];
    int dot_bc[3];
    int cross_bc[3];
    int scalar_triple;
    int cross_a_bc[3];
    
    dot_ab = a_i * b_i + a_j * b_j + a_k * b_k;
    
    cross_ab[0] = a_j * b_k - a_k * b_j;
    cross_ab[1] = a_k * b_i - a_i * b_k;
    cross_ab[2] = a_i * b_j - a_j * b_i;
    
    cross_bc[0] = b_j * c_k - b_k * c_j;
    cross_bc[1] = b_k * c_i - b_i * c_k;
    cross_bc[2] = b_i * c_j - b_j * c_i;
    
    scalar_triple = a_i * cross_bc[0] + a_j * cross_bc[1] + a_k * cross_bc[2];
    
    cross_a_bc[0] = a_j * cross_bc[2] - a_k * cross_bc[1];
    cross_a_bc[1] = a_k * cross_bc[0] - a_i * cross_bc[2];
    cross_a_bc[2] = a_i * cross_bc[1] - a_j * cross_bc[0];
    
    results[0] = dot_ab;
    results[1] = cross_ab[0];
    results[2] = cross_ab[1];
    results[3] = cross_ab[2];
    results[4] = scalar_triple;
    results[5] = cross_a_bc[0];
    results[6] = cross_a_bc[1];
    results[7] = cross_a_bc[2];
    
    return;
}
