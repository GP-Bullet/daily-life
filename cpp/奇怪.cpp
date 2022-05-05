
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s="abc";
	char c[] = { 'a','b','\0','c' };//遇到\0就说明是要结束了
	cout << s << endl;
	s[1] = '\0';//将b字符替换成\0
	string s2="a\0c";
	
	cout << s << endl;
	cout << c << endl;
	cout << s2<< endl;
	s2[1]='b';
	cout << s2 << endl;
	return 0;
}

