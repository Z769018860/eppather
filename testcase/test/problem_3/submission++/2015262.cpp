#include <fstream>
#include <iostream>

using namespace std;

       


int main()
{
    fstream infile;
    fstream outfile;
    infile.open("copycat.in",ios::in);
    outfile.open("copycat.out",ios::out);
	int n;
    infile >> n;
	string str;
    for(int i = 0; i < n; i++)
    {
        infile >> str;
        outfile << str <<endl;
    }
    infile.close();
    outfile.close();
    return 0;
}