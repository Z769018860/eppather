#include <stdio.h>
#include <time.h>

#define MAXLEN 500000
int arr[MAXLEN] = {0};

int PartSort(int left, int right) {
    int key;
    int hole;
    
    hole = left;
    key = arr[left];
    
    while (left < right) {
        while (left < right && arr[right] >= key) {
            right = right - 1;
        }
        arr[hole] = arr[right];
        hole = right;

        while (left < right && arr[left] <= key) {
            left = left + 1;
        }
        arr[hole] = arr[left];
        hole = left;
    }
    
    arr[hole] = key;
    
    return hole;
}

int main() {
    int x,y,j;
    scanf("%d %d", &x, &y);
    for (j=0;j<MAXLEN;j++)
        arr[j]=MAXLEN-j;
    int result=partSort(x,y);
    printf("result：%d\n",result);
    return 0;
}