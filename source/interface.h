#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "Book.h"
#include "Librarian.h"
#include "Log.h"
#include "Register.h"
#include "User.h"
#include <graphics.h>

#define buttonW_Start 400
#define buttonW_End 600

using namespace std;

//很烂的代码，只能设成全局变量了
Log l;
SYSTEMTIME sys;
vector<Book> vec;
Register reg;


enum CurrentPage {
	PAGE_MAIN_MENU,
	PAGE_USER_MENU,
	PAGE_LIBRARIAN_MENU,
	PAGE_USER_REGISTER,
	PAGE_USER_LOGIN,
	PAGE_LIBRARIAN_LOGIN,
	PAGE_BOOK_RETURN,
	PAGE_BOOK_LEND,
	PAGE_BOOK_ADD,
	PAGE_BOOK_DELETE,
	PAGE_BOOK_SEARCH_U,
	PAGE_BOOK_SEARCH_L,
	PAGE_EXIT
};

// 全局变量，用于保存当前页面状态
CurrentPage currentPage = PAGE_MAIN_MENU;

void init()
{
	//初始化
	GetLocalTime(&sys);
	fstream books("Bookmessage.txt");
	for (Book b; books >> b;)
	{
		vec.push_back(b);
	}
	books.close();

	//很烂的代码啊，考验我的组合能力
	int a;
	vector<int> IsLend = { 0 };
}

void start();

//文件头
void change(string a);

bool button_click(int x1, int x2, int y1, int y2, const ExMessage& msg);

void mid_button(int y1, int y2, const char arr[]); //在屏幕中间的按钮

void title(const char arr[]);

void MainMenu();

void UserMenu();

void LibrarianMenu();

void UserLoadPage();

void LibrarianLoadPage();

void UserRegisterPage();//last

void user_register(char* UserName, char* PassWord, char* PassWord2);

void ReturnBookPage();

void return_book(char* number);

void LendBookPage();

void lend_book(char* number);

void AddBookPage();

void add_book(char* code, char* name, char* author, char* sum);

bool check_code(char* code);

void DeleteBookPage();

void delete_book(char* number);

void SearchBookPage_U();

void SearchBookPage_L();

void search_book(char* number);

void inputbox(int left, int right, int top, int bottom, char* text, ExMessage& msg);

void passwordInput(int left, int right, int top, int bottom, char* text, ExMessage& msg);

void passwordDisplay(int left, int right, int top, int bottom, char* text, ExMessage& msg);

void UserLoad(char* UserName, char* PassWord);

void LibrarianLoad(char* UserName, char* PassWord);
//

void change(string a)
{
	HWND hnd;
	hnd = GetHWnd();
	SetWindowText(hnd, a.c_str());
}

bool button_click(int x1, int x2, int y1, int y2, const ExMessage& msg)
{
	return msg.x >= x1 && msg.x <= x2 && msg.y >= y1 && msg.y <= y2;
}

void mid_button(int y1, int y2, const char arr[]) //在屏幕中间的按钮
{
	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	fillrectangle(buttonW_Start, y1, buttonW_End, y2);
	int width = (buttonW_End - buttonW_Start) / 2 - textwidth(arr) / 2;
	int height = (y2 - y1) / 2 - textheight(arr) / 2;
	outtextxy(buttonW_Start + width, y1 + height, arr);
}

void title(const char arr[])
{
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(60, 30, "宋体");
	int width = textwidth(arr) / 2;
	outtextxy(500 - width, 70, arr);
}

void MainMenu()
{
	BeginBatchDraw();
	change("图书馆管理系统");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("图书管理系统");

	//创造按钮
	mid_button(175, 225, "用户注册");
	mid_button(250, 300, "用户登录");
	mid_button(325, 375, "管理员登录");
	mid_button(400, 450, "退出系统");
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_MAIN_MENU)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 175, 225, msg)) {
					currentPage = PAGE_USER_REGISTER;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 250, 300, msg)) {
					currentPage = PAGE_USER_LOGIN;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					currentPage = PAGE_LIBRARIAN_LOGIN;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					exit(0);
					break;
				}
			}
		}
	}
	return;
}

void UserMenu()
{
	BeginBatchDraw();
	change("用户界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("用户操作界面");

	//创造按钮
	mid_button(175, 225, "查看图书");
	mid_button(250, 300, "借书");
	mid_button(325, 375, "还书");
	mid_button(400, 450, "返回");
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_USER_MENU)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 175, 225, msg)) {
					currentPage = PAGE_BOOK_SEARCH_U;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 250, 300, msg)) {
					currentPage = PAGE_BOOK_LEND;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					currentPage = PAGE_BOOK_RETURN;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_MAIN_MENU();
					break;
				}
			}
		}
	}
}

void LibrarianMenu()
{
	BeginBatchDraw();
	change("管理员界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("管理员操作界面");

	//创造按钮
	mid_button(175, 225, "增加图书");
	mid_button(250, 300, "删除图书");
	mid_button(325, 375, "查询图书");
	mid_button(400, 450, "返回");
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_LIBRARIAN_MENU)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 175, 225, msg)) {
					currentPage = PAGE_BOOK_ADD;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 250, 300, msg)) {
					currentPage = PAGE_BOOK_DELETE;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					currentPage = PAGE_BOOK_SEARCH_L;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_MAIN_MENU();
					break;
				}
			}
		}
	}
}

void ReturnBookPage()
{
	BeginBatchDraw();
	change("还书界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("还书界面");

	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "所还书的编号:(格式如001)");

	int w1 = textwidth("所还书的编号:(格式如001)");
	int h1 = textheight("所还书的编号:(格式如001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "还书");
	mid_button(400, 450, "返回");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_RETURN)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_USER_MENU;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					return_book(number);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, number, msg);
					break;
				}
			}
		}
	}

	delete[] number;
}

void return_book(char* number)
{

	if (number[0] == '\0')
	{
		MessageBox(NULL, "编号不能为空", "错误", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "编号请输入数字", "错误", MB_OK);
		return;
	}

	int i, flag1 = 0;
	for (i = 0; i < vec.size(); i++)
	{
		if (strcmp(vec[i].getcode().c_str(), number)==0)
		{
			flag1 = 1;
			break;
		}

	}
	if (flag1 == 0) {
		MessageBox(NULL, "未查找到", "错误", MB_OK);
		return;
	}

	//文件操作
	fstream re("Returnmessage.txt", ios::out | ios::app);
	re << vec[i].getname() << "于" << sys.wYear << "-" << sys.wMonth << "-" << sys.wDay << "-" << sys.wHour << ":" << sys.wMinute << "被" << l.U.Getname() << "交还." << endl;//此处有的Uname估计会出现错误
	vec[i].returned();
	re.close();

	MessageBox(NULL, "还书成功", "提示", MB_OK);
}

void LendBookPage()
{
	BeginBatchDraw();
	change("借书界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("借书界面");

	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "所借书的编号:(格式如001)");

	int w1 = textwidth("所借书的编号:(格式如001)");
	int h1 = textheight("所借书的编号:(格式如001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "借书");
	mid_button(400, 450, "返回");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_LEND)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_USER_MENU;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					lend_book(number);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, number, msg);
					break;
				}
			}
		}
	}

	delete[] number;
}

void lend_book(char* number)
{
	if (number[0] == '\0')
	{
		MessageBox(NULL, "编号不能为空", "错误", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "编号请输入数字", "错误", MB_OK);
		return;
	}

	int i, flag1 = 0;
	for (i = 0; i < vec.size(); i++)
	{
		if (strcmp(vec[i].getcode().c_str(), number)==0)
		{
			flag1 = 1;
			break;
		}

	}
	if (flag1 == 0) {
		MessageBox(NULL, "未查找到或未被借阅", "错误", MB_OK);
		return;
	}

	//文件操作
	fstream re("Lendmessage.txt", ios::out | ios::app);
	re << vec[i].getname() << "于" << sys.wYear << "-" << sys.wMonth << "-" << sys.wDay << "-" << sys.wHour << ":" << sys.wMinute << "被" << l.U.Getname() << "借出." << endl;//此处有的Uname估计会出现错误
	vec[i].returned();
	re.close();

	MessageBox(NULL, "借书成功", "提示", MB_OK);
}

void SearchBookPage_U()
{

	BeginBatchDraw();
	change("查询书界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("查询书界面");

	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "所查书的编号:(格式如001)");

	int w1 = textwidth("所查书的编号:(格式如001)");
	int h1 = textheight("所查书的编号:(格式如001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "查书");
	mid_button(400, 450, "返回");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_SEARCH_U)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_USER_MENU;
					break; 
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					search_book(number);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700,200, 200 + h1, number, msg);
					break;
				}
			}
		}
	}
}

void SearchBookPage_L()
{

	BeginBatchDraw();
	change("查询书界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("查询书界面");

	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "所查书的编号:(格式如001)");

	int w1 = textwidth("所查书的编号:(格式如001)");
	int h1 = textheight("所查书的编号:(格式如001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "查书");
	mid_button(400, 450, "返回");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_SEARCH_L)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_LIBRARIAN_MENU;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					search_book(number);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, number, msg);
					break;
				}
			}
		}
	}
	delete[] number;
}

void search_book(char* number)
{
	char* a = new char[256]; 

	if (number[0] == '\0')
	{
		MessageBox(NULL, "编号不能为空", "错误", MB_OK);
		delete[] a;
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "编号请输入数字", "错误", MB_OK);
		return;
	}

	bool found = false;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].getcode().c_str() << " " << number << " " << strcmp(vec[i].getcode().c_str(), number)<<endl;
		if (strcmp(vec[i].getcode().c_str(), number) == 0)
		{
			strcpy(a, ""); 
			strcat(a, "编号: ");
			strcat(a, vec[i].getcode().c_str());
			strcat(a, "\n书名: ");
			strcat(a, vec[i].getname().c_str());
			strcat(a, "\n作者: ");
			strcat(a, vec[i].getauthor().c_str());
			strcat(a, "\n数量: ");
			strcat(a, to_string(vec[i].getsum()).c_str());

			MessageBox(NULL, a, "书籍信息", MB_OK);
			found = true;
			break; 
		}
	}

	delete[] a;

	if (!found)
	{
		MessageBox(NULL, "未查找到", "书籍信息", MB_OK);
	}
}

void DeleteBookPage()
{
	BeginBatchDraw();
	change("删除书界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("删除书界面");

	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "所删除书的编号:(格式如001)");

	int w1 = textwidth("所删除书的编号:(格式如001)");
	int h1 = textheight("所删除书的编号:(格式如001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "删除");
	mid_button(400, 450, "返回");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_DELETE)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_LIBRARIAN_MENU;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					delete_book(number);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, number, msg);
					break;
				}
			}
		}
	}
}

void delete_book(char* number)
{
	if (number[0] == '\0')
	{
		MessageBox(NULL, "编号不能为空", "错误", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "编号请输入数字", "错误", MB_OK);
		return;
	}

	vector<Book> va;
	vector<Book>::iterator it;
	Book b;
	fstream file("Bookmessage.txt", ios::binary | ios::in); //打开文件
	for (Book b; file >> b;)
	{
		va.push_back(b);
	}
	file.close();

	int flag = 0;

	for (it = va.begin(); it != va.end(); it++)
	{
		if (strcmp(it->getcode().c_str(), number)==0)
		{
			flag = 1;
			va.erase(it);
			break;
		}
	}
	if (flag == 0) {
		MessageBox(NULL, "未查找到", "错误", MB_OK);
		return;
	}

	fstream file1("Bookmessage.txt", ios::out | ios::trunc);
	for (int i = 0; i < va.size(); i++)
	{
		file1 << va[i].getcode() << " " << va[i].getname() << " " << va[i].getauthor() << " " << va[i].getsum() << endl;
		//将未删除的图书写入文件
	}
	file1.close();

	if (flag == 1) MessageBox(NULL, "删除成功", "提示", MB_OK);
}

void AddBookPage()
{
	BeginBatchDraw();
	change("添加书籍界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("添加书籍界面");

	//特殊按钮
	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "书籍编号:");
	outtextxy(300, 250, "书籍名称:");
	int w1 = textwidth("书籍编号:");
	int h1 = textheight("书籍编号:");

	int w2 = textwidth("作者:");

	outtextxy(300 + w1 - w2, 300, "作者:");
	outtextxy(300 + w1 - w2, 350, "数量:");

	fillrectangle(300+w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);
	fillrectangle(300 + w1, 300, 700, 300 + h1);
	fillrectangle(300 + w1, 350, 700, 350 + h1);


	outtextxy(300, 400, "注意!书籍编号格式为001");

	mid_button(430, 480, "添加");
	mid_button(500, 550, "返回");

	EndBatchDraw();

	char* code = new char[28];
	code[0] = '\0';
	char* name = new char[28];
	name[0] = '\0';
	char* author = new char[28];
	author[0] = '\0';
	char* sum = new char[28];
	sum[0] = '\0';

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_BOOK_ADD)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 500,550, msg)) {
					currentPage = PAGE_LIBRARIAN_MENU;
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 430,480, msg)) {
					add_book(code,name,author,sum);
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1,msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1,code, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 250, 250 + h1, msg)) {
					inputbox(300 + w1, 700, 250, 250 + h1, name, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 300, 300 + h1, msg)) {
					inputbox(300 + w1, 700, 300, 300 + h1, author, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 350, 350 + h1, msg)) {
					inputbox(300 + w1, 700, 350, 350 + h1, sum, msg);
					break;
				}
			}
		}
	}
	delete[] code;
	delete[] name;
	delete[] author;
	delete[] sum;
}

void add_book(char* code,char* name,char* author,char* sum)
{
	if (code[0] == '\0' || name[0] == '\0' || author[0] == '\0' || sum[0] == '\0')
	{
		MessageBox(NULL, "请确保填写完整，正确", "错误", MB_OK);
		return;
	}

	Book B;
	B.setcode(code);
	B.setname(name);
	B.setauthor(author);
	try {
		int number =stoi(sum);
		int codenum = stoi(code);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "编号与数量请输入数字", "错误", MB_OK);
		return;
	}

	if (!check_code(code)) {
		MessageBox(NULL, "书籍编号重复", "错误", MB_OK);
		return;
	}

	fstream bookmessage("Bookmessage.txt", ios::app);
	if (bookmessage.is_open())
	{
		bookmessage << B.getcode() << " " << B.getname() << " " << B.getauthor() << " " << B.getsum() << endl;
		MessageBox(NULL, "添加成功", "提示", MB_OK);
		bookmessage.close();
	}
	else MessageBox(NULL, "文件打开失败", "错误", MB_OK);
}

bool check_code(char* code)
{
	vector<Book> va;
	vector<Book>::iterator it;
	Book b;
	fstream file("Bookmessage.txt", ios::binary | ios::in); //打开文件
	for (Book b; file >> b;)
	{
		va.push_back(b);
	}
	file.close();

	for (it = va.begin(); it != va.end(); it++)
	{
		if (strcmp(it->getcode().c_str(),code)==0)
		{
			return false;
		}
	}
	return true;
}

void UserLoadPage()
{
	BeginBatchDraw();
	change("用户登录界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("用户登录界面");

	//特殊按钮
	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "用户名:");
	int w1 = textwidth("用户名:");
	int h1 = textheight("用户名:");

	int w2 = textwidth("密码:");
	int h2 = textheight("密码:");

	outtextxy(300 + w1 - w2, 250, "密码:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);


	mid_button(325, 375, "登录");
	mid_button(400, 450, "返回");


	setbkmode(TRANSPARENT);
	//密码显示按钮,使用图片加载的方式
	IMAGE img2;
	loadimage(&img2, "./眼睛不可见.jpg", 40, h1);
	putimage(710, 250, &img2);

	EndBatchDraw();



	//用于键盘输入保存的数据类型初始化
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_USER_LOGIN)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_MAIN_MENU;
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, UserName, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 250, 250 + h1, msg)) {
					passwordInput(300 + w1, 700, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(710, 750, 250, 250 + h1, msg)) {
					passwordDisplay(710, 750, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					UserLoad(UserName, PassWord);
					break;
				}
			}
		}
	}
	delete[] PassWord;
	delete[] UserName;
}

void LibrarianLoadPage()
{
	BeginBatchDraw();
	change("管理员登录界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("管理员登录界面");

	//特殊按钮
	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "用户名:");
	int w1 = textwidth("用户名:");
	int h1 = textheight("用户名:");

	int w2 = textwidth("密码:");
	int h2 = textheight("密码:");

	outtextxy(300 + w1 - w2, 250, "密码:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);


	mid_button(325, 375, "登录");
	mid_button(400, 450, "返回");

	EndBatchDraw();

	setbkmode(TRANSPARENT);
	//密码显示按钮,使用图片加载的方式
	IMAGE img2;
	loadimage(&img2, "./眼睛不可见.jpg", 40, h1);
	putimage(710, 250, &img2);
	EndBatchDraw();




	//用于键盘输入保存的数据类型初始化
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_LIBRARIAN_LOGIN)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_MAIN_MENU;
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, UserName, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 250, 250 + h1, msg)) {
					passwordInput(300 + w1, 700, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(710, 750, 250, 250 + h1, msg)) {
					passwordDisplay(710, 750, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					LibrarianLoad(UserName, PassWord);
					break;
				}
			}
		}
	}
	delete[] PassWord;
	delete[] UserName;
}

void UserRegisterPage()
{
	BeginBatchDraw();

	change("用户注册界面");
	//设置背景
	cleardevice();
	IMAGE img;
	loadimage(&img, "./草地背景.jpg", 1000, 640);
	putimage(0, 0, &img);

	//打出标题
	title("用户注册界面");

	//特殊按钮
	settextcolor(BLACK);
	settextstyle(30, 10, "微软雅黑");
	outtextxy(300, 200, "用户名:");
	int w1 = textwidth("用户名:");
	int h1 = textheight("用户名:");

	int w2 = textwidth("密码:");
	int h2 = textheight("密码:");

	int w3 = textwidth("请再次输入密码:");

	outtextxy(300 + w1 - w2, 250, "密码:");
	outtextxy(300 + w1 - w3, 300, "请再次输入密码:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);
	fillrectangle(300 + w1, 300, 700, 300 + h1);

	setbkmode(TRANSPARENT);
	//密码显示按钮,使用图片加载的方式
	IMAGE img2;
	loadimage(&img2, "./眼睛不可见.jpg", 40, h1);
	putimage(710, 250, &img2);
	IMAGE img3;
	loadimage(&img3, "./眼睛不可见.jpg", 40, h1);
	putimage(710, 300, &img2);


	mid_button(340, 390, "注册");
	mid_button(400, 450, "返回");

	EndBatchDraw();

	//用于键盘输入保存的数据类型初始化
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	char* PassWord2 = new char[28];
	PassWord2[0] = '\0';

	//鼠标操作
	ExMessage msg;
	while (currentPage == PAGE_USER_REGISTER)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (button_click(buttonW_Start, buttonW_End, 400, 450, msg)) {
					currentPage = PAGE_MAIN_MENU;
					break;
				}
				else if (button_click(300 + w1, 700, 200, 200 + h1, msg)) {
					inputbox(300 + w1, 700, 200, 200 + h1, UserName, msg);
					break;
				}
				else if (button_click(300 + w1, 700, 250, 250 + h1, msg)) {
					passwordInput(300 + w1, 700, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(710, 750, 250, 250 + h1, msg)) {
					passwordDisplay(710, 750, 250, 250 + h1, PassWord, msg);
					break;
				}
				else if (button_click(300 + w1,700,300, 300 + h1, msg)) {
					passwordInput(300 + w1, 700, 300, 300 + h1, PassWord2, msg);
					break;
				}
				else if (button_click(710, 750, 300, 300 + h1, msg)) {
					passwordDisplay(710, 750, 300, 300 + h1, PassWord2, msg);
					break;
				}
				else if (button_click(buttonW_Start, buttonW_End, 325, 375, msg)) {
					user_register(UserName, PassWord, PassWord2);
					break;
				}
			}
		}
	}
	delete[] PassWord;
	delete[] PassWord2;
	delete[] UserName;
}

void user_register(char* UserName, char* PassWord, char* PassWord2)
{
	if (UserName[0] == '\0' || PassWord[0] == '\0' || PassWord2[0] == '\0')
	{
		MessageBox(NULL, "请确保填写完整，正确", "错误", MB_OK);
		return;
	}
	else if (strcmp(PassWord, PassWord2) != 0)
	{
		MessageBox(NULL, "两次密码填写不相同", "错误", MB_OK);
		return;
	}

	User U;

	U.SetID(UserName);
	U.Setname(UserName);
	U.SetKey(PassWord);
	fstream file("Usermessage.txt", ios::out | ios::app);
	file << " " << U.GetID() << " " << U.Getname() << " " << U.Getkey() << endl; //写入文件

	currentPage = PAGE_MAIN_MENU;
	MessageBox(NULL, "注册成功!", "提示", MB_OK);
}

void start()
{
	init();
	while (currentPage != PAGE_EXIT) {
		switch (currentPage) {
		case PAGE_MAIN_MENU:
			MainMenu();
			break;
		case PAGE_USER_REGISTER:
			UserRegisterPage();
			break;
		case PAGE_USER_LOGIN:
			UserLoadPage();
			break;
		case PAGE_LIBRARIAN_LOGIN:
			LibrarianLoadPage();
			break;
		case PAGE_USER_MENU:
			UserMenu();
			break;
		case PAGE_LIBRARIAN_MENU:
			LibrarianMenu();
			break;
		case PAGE_BOOK_ADD:
			AddBookPage();
			break;
		case PAGE_BOOK_DELETE:
			DeleteBookPage();
			break;
		case PAGE_BOOK_LEND:
			LendBookPage();
			break;
		case PAGE_BOOK_RETURN:
			ReturnBookPage();
			break;
		case PAGE_BOOK_SEARCH_U:
			SearchBookPage_U();
			break;
		case PAGE_BOOK_SEARCH_L:
			SearchBookPage_L();
			break;
		}
	}
}

void inputbox(int left, int right, int top, int bottom, char* text, ExMessage& msg)
{

	// 备份环境值
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();

	setlinecolor(LIGHTGRAY);		// 设置画线颜色
	setbkcolor(WHITE);			// 设置背景颜色
	setfillcolor(WHITE);			// 设置填充颜色

	//初始化
	int maxlen = 28;
	int counter = 0;
	bool binput = true;
	int width = textwidth(text);

	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (!button_click(left, right, top, bottom, msg))
				{
					binput = false;
					break;
				}
			}
			else if (msg.message == WM_CHAR)
			{
				size_t len = strlen(text);
				switch (msg.ch)
				{
				case '\b':
					if (len > 0)
					{
						text[len - 1] = '\0';
						width = textwidth(text);
						clearrectangle(left + width, top + 1, right - 1, bottom - 1);//擦除后面的
						counter = 0;
					}
					break;
				case '\r':
					binput = false;
					break;
				case '\n':
					binput = false;
					break;
				default:
					if (len < maxlen - 1)
					{
						text[len++] = msg.ch;
						text[len] = '\0';

						//问题所在
						clearrectangle(left, top, left + 10 + width + 1, bottom);// 擦除之前的输入
						width = textwidth(text);
						counter = 0;
						outtextxy(left + 1, top + 1, text);
					}
					break;
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);
		}
		//绘制光标(光标闪烁周期为20ms*32)
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		else
			clearrectangle(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		Sleep(20);
	}

	clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 擦光标


	fillrectangle(left, top, right, bottom);
	outtextxy(left + 1, top + 1, text);



	// 恢复环境值
	setlinecolor(oldlinecolor);
	setbkcolor(oldbkcolor);
	setfillcolor(oldfillcolor);
}

void passwordInput(int left, int right, int top, int bottom, char* text, ExMessage& msg)
{

	setlinecolor(LIGHTGRAY);		// 设置画线颜色
	setbkcolor(WHITE);			// 设置背景颜色
	setfillcolor(WHITE);			// 设置填充颜色

	//初始化
	int maxlen = 28;
	int counter = 0;
	bool binput = true;
	char* mask = new char[28];
	int textlen = strlen(text);
	for (int i = 0; i < textlen; i++) mask[i] = '*';
	mask[textlen] = '\0';

	int width = textwidth(mask);


	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (!button_click(left, right, top, bottom, msg))
				{
					binput = false;
					break;
				}
			}
			else if (msg.message == WM_CHAR)
			{
				size_t len = strlen(text);
				switch (msg.ch)
				{
				case '\b':
					if (len > 0)
					{
						text[len - 1] = '\0';
						mask[len - 1] = '\0';

						width = textwidth(mask);
						clearrectangle(left + width, top + 1, right - 1, bottom - 1);//擦除后面的
						counter = 0;
					}
					break;
				case '\r':
					binput = false;
					break;
				case '\n':
					binput = false;
					break;
				default:
					if (len < maxlen - 1)
					{
						text[len++] = msg.ch;
						text[len] = '\0';
						mask[len - 1] = '*';
						mask[len] = '\0';

						clearrectangle(left, top, left + 10 + width + 1, bottom);// 擦除之前的输入
						width = textwidth(mask);
						counter = 0;
						outtextxy(left + 1, top + 1, mask);
					}
					break;
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);
		}
		//绘制光标(光标闪烁周期为20ms*32)
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		else
			clearrectangle(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		Sleep(20);
	}

	clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// 擦光标


	fillrectangle(left, top, right, bottom);
	outtextxy(left + 1, top + 1, mask);




}

void passwordDisplay(int left, int right, int top, int bottom, char* text, ExMessage& msg)
{
	//变为可见
	IMAGE img2;
	loadimage(&img2, "./眼睛可见.jpg", 40, 30);
	putimage(left,top, &img2);



	clearrectangle(365, top, 700, bottom);
	fillrectangle(365, top, 700, bottom);
	outtextxy(365 + 1, top + 1, text);

	//掩码准备
	char* mask = new char[28];
	int textlen = strlen(text);
	for (int i = 0; i < textlen; i++) mask[i] = '*';
	mask[textlen] = '\0';

	bool binput = true;


	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE, false))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (!button_click(left, right, top, bottom, msg))
				{
					cout << "1" << endl;
					binput = false;
					clearrectangle(365, top, 700, bottom);
					fillrectangle(365, top, 700, bottom);
					loadimage(&img2, "./眼睛不可见.jpg", 40, 30);
					putimage(710, 250, &img2);
					outtextxy(365, top + 1, mask);
					break;
				}
			}
			peekmessage(NULL, EX_MOUSE);
		}
	}

	delete[] mask;
}

void UserLoad(char* UserName, char* PassWord)
{
	if (UserName[0] == '\0' || PassWord[0] == '\0')
	{
		MessageBox(NULL, "用户名或密码未输入", "错误", MB_OKCANCEL);
	}
	else if (!l.checkUser(UserName, PassWord))
	{
		MessageBox(NULL, "用户名或密码输入错误", "错误", MB_OKCANCEL);
	}
	else if (l.checkUser(UserName, PassWord))
	{
		currentPage = PAGE_USER_MENU;
		MessageBox(NULL, "登录成功", "提示", MB_OKCANCEL);
		UserMenu();
	}
}

void LibrarianLoad(char* UserName, char* PassWord)
{
	if (UserName[0] == '\0' || PassWord[0] == '\0')
	{
		MessageBox(NULL, "用户名或密码未输入", "错误", MB_OKCANCEL);
	}
	else if (!l.Librarian_log(UserName, PassWord))
	{
		MessageBox(NULL, "用户名或密码输入错误", "错误", MB_OKCANCEL);
	}
	else if (l.Librarian_log(UserName, PassWord))
	{
		currentPage = PAGE_LIBRARIAN_MENU;
		MessageBox(NULL, "登录成功", "提示", MB_OKCANCEL);
		LibrarianMenu();
	}
}