int is_pangram(const char *s)
{
    char wasused[26] = {0};
    int total = 0;
    int i;
    int j;
    char ch;
    char alpha_lower[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char alpha_upper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    for (i = 0; s[i] != '\0'; i = i + 1) {
        ch = s[i];
        int found = 0;
        int idx = 0;
        
        for (j = 0; j < 26; j = j + 1) {
            if (ch == alpha_lower[j] || ch == alpha_upper[j]) {
                found = 1;
                idx = j;
                break;
            }
        }
        
        if (found == 0) {
            continue;
        }
        
        if (wasused[idx] == 0) {
            total = total + 1;
            wasused[idx] = 1;
        }
        
        if (total == 26) {
            return 1;
        }
    }
    
    return 0;
    return;
}
