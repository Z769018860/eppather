void b_write(int buf[5], int n_bits, int shift, int bf[3])
{
    int accu = bf[1];
    int bits = bf[2];
    int buf_offset = shift / 8;
    shift = shift % 8;

    for (; n_bits != 0 || bits >= 8; )
    {
        for (; bits >= 8; )
        {
            bits = bits - 8;
            accu = accu & ((1 << bits) - 1);
        }
        for (; bits < 8 && n_bits != 0; )
        {
            accu = (accu << 1) | (((128 >> shift) & buf[buf_offset]) >> (7 - shift));
            n_bits = n_bits - 1;
            bits = bits + 1;
            shift = shift + 1;
            if (shift == 8)
            {
                shift = 0;
                buf_offset = buf_offset + 1;
            }
        }
    }
    bf[1] = accu;
    bf[2] = bits;
    return;
}

void b_read(int buf[5], int n_bits, int shift, int bf[3])
{
    int accu = bf[1];
    int bits = bf[2];
    int mask;
    int i = 0;
    int buf_offset = shift / 8;
    shift = shift % 8;

    for (; n_bits != 0; )
    {
        for (; bits != 0 && n_bits != 0; )
        {
            mask = 128 >> shift;
            if (accu & (1 << (bits - 1)))
            {
                buf[buf_offset] = buf[buf_offset] | mask;
            }
            else
            {
                buf[buf_offset] = buf[buf_offset] & ~mask;
            }
            n_bits = n_bits - 1;
            bits = bits - 1;
            shift = shift + 1;
            if (shift >= 8)
            {
                shift = 0;
                buf_offset = buf_offset + 1;
            }
        }
        if (n_bits == 0)
        {
            break;
        }
        bits = bits + 8;
    }
    bf[1] = accu;
    bf[2] = bits;
    return;
}

void b_detach(int bf[3])
{
    if (bf[2] != 0)
    {
        bf[1] = bf[1] << (8 - bf[2]);
    }
    return;
}
