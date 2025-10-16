int vector_ops(int a_i, int a_j, int a_k, int b_i, int b_j, int b_k, int c_i, int c_j, int c_k, int op, int result[5]) {
    int dot_product;
    int cross_product[3];
    int scalar_triple_product;
    int vector_triple_product[3];
    
    if (op == 0) {
        dot_product = a_i * b_i + a_j * b_j + a_k * b_k;
        result[0] = dot_product;
    } else {
        if (op == 1) {
            cross_product[0] = a_j * b_k - a_k * b_j;
            cross_product[1] = a_k * b_i - a_i * b_k;
            cross_product[2] = a_i * b_j - a_j * b_i;
            result[0] = cross_product[0];
            result[1] = cross_product[1];
            result[2] = cross_product[2];
        } else {
            if (op == 2) {
                cross_product[0] = b_j * c_k - b_k * c_j;
                cross_product[1] = b_k * c_i - b_i * c_k;
                cross_product[2] = b_i * c_j - b_j * c_i;
                scalar_triple_product = a_i * cross_product[0] + a_j * cross_product[1] + a_k * cross_product[2];
                result[0] = scalar_triple_product;
            } else {
                if (op == 3) {
                    cross_product[0] = b_j * c_k - b_k * c_j;
                    cross_product[1] = b_k * c_i - b_i * c_k;
                    cross_product[2] = b_i * c_j - b_j * c_i;
                    vector_triple_product[0] = a_j * cross_product[2] - a_k * cross_product[1];
                    vector_triple_product[1] = a_k * cross_product[0] - a_i * cross_product[2];
                    vector_triple_product[2] = a_i * cross_product[1] - a_j * cross_product[0];
                    result[0] = vector_triple_product[0];
                    result[1] = vector_triple_product[1];
                    result[2] = vector_triple_product[2];
                }
            }
        }
    }
    return;
}
