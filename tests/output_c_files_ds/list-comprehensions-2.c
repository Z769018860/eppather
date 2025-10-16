int i;
for (i = f + 1; i <= t; i = i + 1) {
    e = e->nx = listNew(sizeof(i), &i);
}
return;
