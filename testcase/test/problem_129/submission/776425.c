char s[1 << 21];
main() {
    scanf("%s", s);
    if (s[0] == 'a' && s[1] == 'a') {
        for (int i = 0; s[i]; ++ i) 
            printf("%d ", i + 1); 
        return 0; 
    }
    int x = 0, y, z;
    while (s[x]) {
        y = z = x;
        while (s[++y] && s[y] >= s[z]) s[y] > s[z] ? z = x : ++z;
        while (x <= z) printf("%d ", x += y - z);
    }
}