#include<iostream>
using namespace std;
void getNext(int *next,string str)
{
	int j = 0, i;
	next[0] = 0;
	for (i = 1; i < str.size(); i++) {
		while (j > 0 && str[j] != str[i]) {
			j = next[j - 1];
		}
		if (str[i] == str[j])
		{
			j++;
		}
		next[i] = j;
	}
}
int main()
{
	int ans = 0;
	string s, str;
	cin >> s >> str;
	int *next=new int[str.size()];
	getNext(next, str);
	int j = 0;
	for (int i = 0; i < s.size(); i++) {
		while (j > 0 && s[i] != str[j]) {
			j = next[j - 1];
		}
		if (s[i] == str[j])
		{
			j++;
		}
		if (j == str.size())
		{
			
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}