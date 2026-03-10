int main(){
    int n;
    int sum;
    int i;
    n = 12;
    sum = 0;
    for(i = 1; i < 6; i = i + 1){
        if(n % i == 0){
            sum = sum + i;
        }
    }
    if (sum > n) {
        sum = sum - n;
    }
    return 0;
}
