int* myFuncComplex(int* (*funcParameter)(int* parameter))
{
    int inLong;
    int outDouble[1];
    int* inLong2;
    inLong2 = &inLong;
    outDouble[0] = (*funcParameter)(&inLong);
    outDouble[0] = funcParameter(inLong2)[0];
    return;
}
