int* myFuncComplex(int* funcParameter) {
    int inLong[5];
    int outDouble[5];
    int inLong2[5];
    inLong2[0] = inLong[0];
    
    outDouble[0] = (*funcParameter)(&inLong[0]);
    outDouble[0] = funcParameter(inLong2);
    
    return;
}
