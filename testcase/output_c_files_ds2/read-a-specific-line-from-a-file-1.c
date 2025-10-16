int read_file_line(int path, int line_no)
{
    int s[5];
    int buf[5];
    int start[5];
    int end[5];
    int i[5];
    int ln[5];
    int fd[5];
    int ret[5];
    
    start[0] = -1;
    end[0] = -1;
    ret[0] = 1;
    
    if (line_no == 1)
    {
        start[0] = 0;
    }
    else if (line_no < 1)
    {
        return 0;
    }
    
    line_no = line_no - 1;
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        buf[i[0]] = 0;
    }
    
    ln[0] = 0;
    for (i[0] = 0; i[0] < 5 && ln[0] <= line_no; i[0] = i[0] + 1)
    {
        if (buf[i[0]] != 10)
        {
            continue;
        }
        
        ln[0] = ln[0] + 1;
        if (ln[0] == line_no)
        {
            start[0] = i[0] + 1;
        }
        else if (ln[0] == line_no + 1)
        {
            end[0] = i[0] + 1;
        }
    }
    
    if (start[0] >= 5 || start[0] < 0)
    {
        ret[0] = 0;
    }
    
    return ret[0];
}
