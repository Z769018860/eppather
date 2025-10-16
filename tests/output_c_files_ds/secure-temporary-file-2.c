int generate_temp_filename(char filename[15])
{
    int i;
    for (i = 0; i < 6; i = i + 1)
    {
        filename[i + 9] = 'A' + (i % 26);
    }
    filename[15] = '\0';
    return 0;
}
