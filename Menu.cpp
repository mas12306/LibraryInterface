#include "Menu.h"

int Menu::select()
{
	int op = -1;
	cout << "请选择操作：";
	cin >> op;

	// 如果输入不是一个数字
	while (cin.fail()) {
		cin.clear(); // 清除错误状态
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略缓冲区中的所有字符
		cout << "输入错误，请重新选择操作：";
		cin >> op;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除换行符

	return op;
}

int Menu::mainMenu()
{
	cout << "          主菜单          \n";
	cout << "**************************\n";
	cout << "      1.读者管理          \n";
	cout << "      2.管理员管理        \n";
	cout << "      3.退出系统          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 3))
	{
		cout << "输入数据错误，请重新输入！" << endl;
	}
	return op;
}

int Menu::UserMenu()
{
	cout << "        读者菜单          \n";
	cout << "**************************\n";
	cout << "      1.借阅书籍          \n";
	cout << "      2.归还书籍          \n";
	cout << "      3.查找书籍          \n";
	cout << "      4.返回主菜单        \n";
	cout << "      5.退出系统          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 5))
	{
		cout << "输入数据错误，请重新输入！" << endl;
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
	cout << "        管理员菜单        \n";
	cout << "**************************\n";
	cout << "      1.添加书籍          \n";
	cout << "      2.删除书籍          \n";
	cout << "      3.查找书籍          \n";
	cout << "      4.查看全部书籍      \n";
	cout << "      5.返回主菜单        \n";
	cout << "      6.退出系统          \n";
	cout << "**************************\n";
	cout << endl;
	int op = -1;
	while ((op = select()) && (op < 1 || op > 6))
	{
		cout << "输入数据错误，请重新输入！" << endl;
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