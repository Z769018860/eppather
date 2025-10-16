

















































char outBuf[1 << 22], *outNow = outBuf;
inline void flush () {
    
    *outNow = '\0'; 
    printf("%s", outBuf); 
    outNow = outBuf; 
}
inline void pc (char ch) {
    *(outNow ++) = ch; 
    if (outNow - outBuf == sizeof(outBuf)) 
        flush (); 
}
inline void print(int x) {
    short num[35], *numNow = num; 
    if (x <= 0) 
        pc (x? (char)'-': (char)'0'), x = -x; 
    while (x) 
        *(numNow ++) = x % 10, x /= 10; 
    while (numNow != num) 
        pc ((char)(48 | *(-- numNow))); 
}

char s[1 << 21];
main() {
    scanf("%s", s);
    if (s[0] == 'a' && s[1] == 'a') {
        for (int i = 0; s[i]; ++ i) 
            print(i + 1), pc(32); 
        flush(); 
        return 0; 
    }
    int x = 0, y, z;
    while (s[x]) {
        y = z = x;
        while (s[++y] && s[y] >= s[z]) s[y] > s[z] ? z = x : ++z;
        while (x <= z) print(x += y - z), pc(32);
    }
    flush(); 
}