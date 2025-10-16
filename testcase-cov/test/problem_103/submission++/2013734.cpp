#include <iostream>
#include <vector>
#include <string>

void computeLPSArray(const std::string& pattern, std::vector<int>& lps) {
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(const std::string& text, const std::string& pattern) {
    int m = pattern.length();
    int n = text.length();
    int count = 0;

    std::vector<int> lps(m, 0);
    computeLPSArray(pattern, lps);

    int i = 0;  
    int j = 0;  

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            
            count++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return count;
}

int main() {
    std::string text, pattern;
    std::cin >> text;
    std::cin >> pattern;

    int result = KMPSearch(text, pattern);

    std::cout << result  << std::endl;

    return 0;
}