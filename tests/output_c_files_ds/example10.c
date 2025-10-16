int getop(char s[],int* index){ 
    int i; 
    char c; 
    i=0; 
    for(;;){ 
        c=s[*index]; 
        *index=*index+1; 
        if(c==' '||c=='\t'){} 
        else{break;} 
    } 
    if((c>='0'&&c<='9')==0&&c!='.'){ 
        return c; 
    } 
    if(c>='0'&&c<='9'){ 
        s[i]=c; 
        i=i+1; 
        for(;;){ 
            c=s[*index]; 
            *index=*index+1; 
            if(c>='0'&&c<='9'){ 
                s[i]=c; 
                i=i+1; 
            } 
            else{break;} 
        } 
    } 
    if(c=='.'){ 
        s[i]=c; 
        i=i+1; 
        for(;;){ 
            c=s[*index]; 
            *index=*index+1; 
            if(c>='0'&&c<='9'){ 
                s[i]=c; 
                i=i+1; 
            } 
            else{break;} 
        } 
    } 
    s[i]='\0'; 
    *index=*index-1; 
    return '0'; 
    return; 
}
