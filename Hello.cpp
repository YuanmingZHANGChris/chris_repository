#include <iostream>
#include <string>
#include "stdio.h"
using namespace std;
int main()
{
			string name1,name2;
			int age;
			string password, mima;
			cout << "����������:";
			cin >> name1;
			cout << "����������:";
			cin >> password;
			cout << "���ٴ���������:";
			cin >> mima;
			cout << "����������:";
			cin >> age;
			cout << "Hello world!" << endl;
			cout << "�ҵ����ֽ�" << name1 << ",�ҽ���" << age << ",����" << age + 1 << "����" << endl;
			if (password == mima)
				cout << "password correct" << endl;
			else
				cout << "password error" << endl;
			while (password == mima)
			{
				cout << "����" << endl;

			}

			system("pause");
		
			return 0;
	
}
