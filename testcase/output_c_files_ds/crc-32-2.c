uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len)
{
    uint32_t table[256];
    uint32_t rem;
    uint8_t octet;
    int i;
    int j;
    const char *p;
    const char *q;
    int have_table;
    
    have_table = 0;
    if (have_table == 0)
    {
        for (i = 0; i < 256; i = i + 1)
        {
            rem = i;
            for (j = 0; j < 8; j = j + 1)
            {
                if ((rem & 1) != 0)
                {
                    rem = rem >> 1;
                    rem = rem ^ 0xedb88320;
                }
                else
                {
                    rem = rem >> 1;
                }
            }
            table[i] = rem;
        }
        have_table = 1;
    }
    
    crc = ~crc;
    q = buf + len;
    for (p = buf; p < q; p = p + 1)
    {
        octet = *p;
        crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
    }
    return ~crc;
}
