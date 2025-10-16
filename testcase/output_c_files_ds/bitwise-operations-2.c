unsigned int rotr(unsigned int x, unsigned int s)
{
    unsigned int result;
    unsigned int temp1;
    unsigned int temp2;
    temp1 = x >> s;
    temp2 = x << (32 - s);
    result = temp1 | temp2;
    return result;
}
