void anynacci(int seedArray[5], int howMany, int result[5])
{
    int i;
    int j;
    int initialCardinality;
    int n;
    
    initialCardinality = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (seedArray[i] != 0)
        {
            initialCardinality = initialCardinality + 1;
        }
        else
        {
            break;
        }
    }
    
    for (i = 0; i < initialCardinality; i = i + 1)
    {
        result[i] = seedArray[i];
    }
    
    n = 5;
    if (howMany < n)
    {
        n = howMany;
    }
    
    for (i = initialCardinality; i < n; i = i + 1)
    {
        result[i] = 0;
        for (j = i - initialCardinality; j < i; j = j + 1)
        {
            result[i] = result[i] + result[j];
        }
    }
    return;
}
