
void bubble()
{
int a[5];
int b[5] = {1,2,3,4,5};
int i, j;
int lx;
i = 4;
while (i > 0) {
lx = 0;
j = 0;
while (j < i) {
if (a[j+1] < a[j]) {
a[j+1] = a[j];
a[j] = a[j+1];
lx = j;
}
j = j+1;
}
i = lx;
}
}