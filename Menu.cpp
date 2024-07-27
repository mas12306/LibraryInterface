#include "Menu.h"

int Menu::select()
{
	int op = -1;
	cout << "��ѡ�������";
	cin >> op;

	// ������벻��һ������
	while (cin.fail()) {
		cin.clear(); // �������״̬
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Ի������е������ַ�
		cout << "�������������ѡ�������";
		cin >> op;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������з�

	return op;
}

int Menu::mainMenu()
{
	cout << "          ���˵�          \n";
	cout << "**************************\n";
	cout << "      1.���߹���          \n";
	cout << "      2.����Ա����        \n";
	cout << "      3.�˳�ϵͳ          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 3))
	{
		cout << "�������ݴ������������룡" << endl;
	}
	return op;
}

int Menu::UserMenu()
{
	cout << "        ���߲˵�          \n";
	cout << "**************************\n";
	cout << "      1.�����鼮          \n";
	cout << "      2.�黹�鼮          \n";
	cout << "      3.�����鼮          \n";
	cout << "      4.�������˵�        \n";
	cout << "      5.�˳�ϵͳ          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 5))
	{
		cout << "�������ݴ������������룡" << endl;
	}
	return op;
}

void Menu::User_manage()
{
	User now;
	bool isdone = false;
	while (!isdone)
	{
		int op = UserMenu();
		switch (op)
		{
		case 1:
			now.lend_book();
			break;
		case 2:
			now.return_book();
			break;
		case 3:
			now.search_book();
			break;
		case 4:
			isdone = true;
			break;
		case 5:
			exit(0);
			break;
		}
	}
}

int Menu::adminUserMenu()
{
	cout << "        ����Ա�˵�        \n";
	cout << "**************************\n";
	cout << "      1.����鼮          \n";
	cout << "      2.ɾ���鼮          \n";
	cout << "      3.�����鼮          \n";
	cout << "      4.�鿴ȫ���鼮      \n";
	cout << "      5.�������˵�        \n";
	cout << "      6.�˳�ϵͳ          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 6))
	{
		cout << "�������ݴ������������룡" << endl;
	}
	return op;
}

void Menu::adminUser_manage()
{
	adminUser now;
	bool isdone = false;
	while (!isdone)
	{
		int op = adminUserMenu();
		switch (op)
		{
		case 1:
			now.add_book();
			break;
		case 2:
			now.remove_book();
			break;
		case 3:
			now.search_book();
			break;
		case 4:
			now.review();
			break;
		case 5:
			isdone = true;
			break;
		case 6:
			exit(0);
			break;
		}
	}
}

void Menu::run()
{
	int op =-1;
	while (op = mainMenu())
	{
		switch (op)
		{
		case 1:
			User_manage();
			break;
		case 2:
			adminUser_manage();
			break;
		case 3:
			exit(0);
			break;
		}
	}
}