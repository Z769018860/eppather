int compute_overflow_examples() {
    int signed32_results[5];
    signed32_results[0] = -(-2147483647-1);
    signed32_results[1] = 2000000000 + 2000000000;
    signed32_results[2] = -2147483647 - 2147483647;
    signed32_results[3] = 46341 * 46341;
    signed32_results[4] = (-2147483647-1) / -1;

    long signed64_results[5];
    signed64_results[0] = -(-9223372036854775807-1);
    signed64_results[1] = 5000000000000000000+5000000000000000000;
    signed64_results[2] = -9223372036854775807 - 9223372036854775807;
    signed64_results[3] = 3037000500 * 3037000500;
    signed64_results[4] = (-9223372036854775807-1) / -1;

    unsigned int unsigned32_results[4];
    unsigned32_results[0] = -4294967295U;
    unsigned32_results[1] = 3000000000U + 3000000000U;
    unsigned32_results[2] = 2147483647U - 4294967295U;
    unsigned32_results[3] = 65537U * 65537U;

    unsigned long unsigned64_results[4];
    unsigned64_results[0] = -18446744073709551615LU;
    unsigned64_results[1] = 10000000000000000000LU + 10000000000000000000LU;
    unsigned64_results[2] = 9223372036854775807LU - 18446744073709551615LU;
    unsigned64_results[3] = 4294967296LU * 4294967296LU;

    return;
}
