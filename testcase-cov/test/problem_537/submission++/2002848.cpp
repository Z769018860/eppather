#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll=long long;
signed main(){
    std::unordered_map<std::string,int> mp;
    std::string s;
    int k;
    std::cin>>s>>k;
    int mx=0;
    for(int i=0;i<s.size();i++){
        std::string s1=s.substr(i,k);
        mp[s1]++;
        mx=std::max(mx,mp[s1]);
    }
    std::cout<<mx<<'\n';
    return 0;
}