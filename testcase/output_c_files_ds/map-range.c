int mapRange(int a1, int a2, int b1, int b2, int s)
{
    int result;
    result = b1 + (s - a1) * (b2 - b1) / (a2 - a1);
    return result;
}

int main()
{
    int i;
    int arr[11];
    for (i = 0; i <= 10; i = i + 1)
    {
        arr[i] = mapRange(0, 10, -1, 0, i);
    }
    return;
}
