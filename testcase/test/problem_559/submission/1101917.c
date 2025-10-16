#include<stdio.h>
int x;
int main()
{
    while(1)
    {
        puts("reach_dest");
        fflush(stdout);
        scanf("%d",&x);
        printf("move_left\n");
        fflush(stdout);
        scanf("%d",&x);
    }
    return 0;
}