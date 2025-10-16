int sequential_search(){
    int arr[5];
    int len;
    int n;
    int i;
        for(;i<n;i=i+1){
            if(arr[i]==n)
            {
                return i;
            }
        }
        return -1;
}