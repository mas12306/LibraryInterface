#pragma once

#include "book.h";
#include "User.h"

class Menu
{
public:

	void run() ;

	int mainMenu() ;

	int UserMenu() ;

	int adminUserMenu() ;

	int select() ;

	void User_manage();

	void adminUser_manage();
};

