void findIncDecSequence(int*arr,int size,int*inc,int*dec){ 
    *inc=1; 
    *dec=1; 
    int i; 
    for(i=1;i<size;i=i+1){ 
        if(arr[i]>arr[i-1]){ 
            *inc=*inc+1; 
        }else{ 
            break; 
        } 
    } 
    for(;i<size;i=i+1){ 
        if(arr[i]<arr[i-1]){ 
            *dec=*dec+1; 
        }else{ 
            break; 
        } 
    } 
    return; 
}
