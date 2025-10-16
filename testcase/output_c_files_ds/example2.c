int threeSum(int* arr,int size,int target){
    int i;
    int j;
    int k;
    for(i=0;i<size-2;i=i+1){
        for(j=i+1;j<size-1;j=j+1){
            for(k=j+1;k<size;k=k+1){
                if((*(arr+i)+*(arr+j)+*(arr+k))==target){
                    return 1;
                }
            }
        }
    }
    return 0;
}
