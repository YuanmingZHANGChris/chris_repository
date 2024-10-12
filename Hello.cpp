#include <iostream>
#include <string>
#include "stdio.h"
using namespace std;
int main()
{
			string name1,name2;
			int age;
			string password, mima;
			cout << "请输入名字:";
			cin >> name1;
			cout << "请输入密码:";
			cin >> password;
			cout << "请再次输入密码:";
			cin >> mima;
			cout << "请输入年龄:";
			cin >> age;
			cout << "Hello world!" << endl;
			cout << "我的名字叫" << name1 << ",我今年" << age << ",明年" << age + 1 << "岁了" << endl;
			if (password == mima)
				cout << "password correct" << endl;
			else
				cout << "password error" << endl;
			while (password == mima)
			{
				cout << "呆着" << endl;

			}

			system("pause");
		
			return 0;
	
}
