#include <iostream>
#include <string>

int main()
{
    freopen("copycat.in","r",stdin);
    freopen("copycat.out","w",stdout);
    int T;
    std::cin >> T;
    while (T--)
    {
        std::string s;
        std::cin >> s;
        std::cout << s << "\n";
    }
    return 0;
}