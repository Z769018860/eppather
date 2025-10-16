unsigned int rotr(unsigned int x, unsigned int s)
{
    unsigned int temp[5];
    temp[0] = x;
    unsigned int temp1[5];
    temp1[0] = s;
    unsigned int temp2[5];
    temp2[0] = 32;
    unsigned int temp3[5];
    temp3[0] = temp[0] >> temp1[0];
    unsigned int temp4[5];
    temp4[0] = temp2[0] - temp1[0];
    unsigned int temp5[5];
    temp5[0] = temp[0] << temp4[0];
    unsigned int temp6[5];
    temp6[0] = temp3[0] | temp5[0];
    return temp6[0];
}
