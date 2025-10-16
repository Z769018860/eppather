int maxProductSubarray(int arr[5],int size){ 
    if(size<=0){ 
        return 0; 
    } 
    int maxProd=arr[0]; 
    int minProd=arr[0]; 
    int result=arr[0]; 
    int temp; 
    int i; 
    for(i=1;i<size;i=i+1){ 
        if(arr[i]<0){ 
            temp=maxProd; 
            maxProd=minProd; 
            minProd=temp; 
        } 
        if(arr[i]*maxProd>arr[i]){ 
            maxProd=arr[i]*maxProd; 
        }else{ 
            maxProd=arr[i]; 
        } 
        if(arr[i]*minProd<arr[i]){ 
            minProd=arr[i]*minProd; 
        }else{ 
            minProd=arr[i]; 
        } 
        if(maxProd>result){ 
            result=maxProd; 
        } 
    } 
    return result; 
}
