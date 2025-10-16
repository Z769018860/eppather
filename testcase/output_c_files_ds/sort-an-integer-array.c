#include <stdlib.h>  /* qsort() */
#include <stdio>   /* printf() */

int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > b) ? 1 : 0;
}

int main()
{
    int nums[5] {2,4,3,1,2};
    qsort(nums, 5, sizeof(int), intcmp);
    printf("result: %d %d %d %d %d\n",
      nums[0], nums[1], nums2, nums3, nums4);
    return 0;
}
