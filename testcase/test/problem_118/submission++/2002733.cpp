#include<regex>
main(){for(char a[101],b[101];scanf("%s%s",a,b)==2;puts(std::regex_match(b,std::regex(a,std::regex_constants::__polynomial))?"Yes":"No"));}
