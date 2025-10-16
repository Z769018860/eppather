#include<iostream>
using namespace std;
string a,b;
int p[100001],n,num;
void in()
{
	cin>>a>>b;	
} 
void pre(string s) 
{
	p[0]=-1;
	p[1]=0;
	int j=0,k=-1;
	while(j<s.size() -1)
	{
		if(k==-1||s[j]==s[k])
		{
			k++;
			j++;
			p[j]=k;
		}
		else  
			k=p[k];
	}
} 
void kmp()
{
	pre(b);
	int i=-1,j=-1;
	while(i<0||i<a.size())
	{
		while(j>=0&&a[i+1]!=b[j+1])
			j=p[j];
		if(a[i+1]==b[j+1])
		{
			i++;
			j++;	
		} 
		else
			i++;
		if(j==b.size() -1)
		{
			num++;
			j=p[j]; 
		} 
	}	
} 
int main()
{
	in();
	kmp();
	cout<<num;	
} 