void myFuncSimple(void (*funcParameter)(void))
{
    int temp[5];
    temp[0] = 0;
    for (temp[0] = 0; temp[0] < 5; temp[0] = temp[0] + 1)
    {
    }
    (*funcParameter)();
    funcParameter();
    return;
}
