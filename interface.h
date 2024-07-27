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

//���õĴ��룬ֻ�����ȫ�ֱ�����
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

// ȫ�ֱ��������ڱ��浱ǰҳ��״̬
CurrentPage currentPage = PAGE_MAIN_MENU;

void init()
{
	//��ʼ��
	GetLocalTime(&sys);
	fstream books("Bookmessage.txt");
	for (Book b; books >> b;)
	{
		vec.push_back(b);
	}
	books.close();

	//���õĴ��밡�������ҵ��������
	int a;
	vector<int> IsLend = { 0 };
}

void start();

//�ļ�ͷ
void change(string a);

bool button_click(int x1, int x2, int y1, int y2, const ExMessage& msg);

void mid_button(int y1, int y2, const char arr[]); //����Ļ�м�İ�ť

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

void mid_button(int y1, int y2, const char arr[]) //����Ļ�м�İ�ť
{
	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	fillrectangle(buttonW_Start, y1, buttonW_End, y2);
	int width = (buttonW_End - buttonW_Start) / 2 - textwidth(arr) / 2;
	int height = (y2 - y1) / 2 - textheight(arr) / 2;
	outtextxy(buttonW_Start + width, y1 + height, arr);
}

void title(const char arr[])
{
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(60, 30, "����");
	int width = textwidth(arr) / 2;
	outtextxy(500 - width, 70, arr);
}

void MainMenu()
{
	BeginBatchDraw();
	change("ͼ��ݹ���ϵͳ");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("ͼ�����ϵͳ");

	//���찴ť
	mid_button(175, 225, "�û�ע��");
	mid_button(250, 300, "�û���¼");
	mid_button(325, 375, "����Ա��¼");
	mid_button(400, 450, "�˳�ϵͳ");
	EndBatchDraw();

	//������
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
	change("�û�����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("�û���������");

	//���찴ť
	mid_button(175, 225, "�鿴ͼ��");
	mid_button(250, 300, "����");
	mid_button(325, 375, "����");
	mid_button(400, 450, "����");
	EndBatchDraw();

	//������
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
	change("����Ա����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("����Ա��������");

	//���찴ť
	mid_button(175, 225, "����ͼ��");
	mid_button(250, 300, "ɾ��ͼ��");
	mid_button(325, 375, "��ѯͼ��");
	mid_button(400, 450, "����");
	EndBatchDraw();

	//������
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
	change("�������");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("�������");

	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "������ı��:(��ʽ��001)");

	int w1 = textwidth("������ı��:(��ʽ��001)");
	int h1 = textheight("������ı��:(��ʽ��001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "����");
	mid_button(400, 450, "����");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//������
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
		MessageBox(NULL, "��Ų���Ϊ��", "����", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "�������������", "����", MB_OK);
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
		MessageBox(NULL, "δ���ҵ�", "����", MB_OK);
		return;
	}

	//�ļ�����
	fstream re("Returnmessage.txt", ios::out | ios::app);
	re << vec[i].getname() << "��" << sys.wYear << "-" << sys.wMonth << "-" << sys.wDay << "-" << sys.wHour << ":" << sys.wMinute << "��" << l.U.Getname() << "����." << endl;//�˴��е�Uname���ƻ���ִ���
	vec[i].returned();
	re.close();

	MessageBox(NULL, "����ɹ�", "��ʾ", MB_OK);
}

void LendBookPage()
{
	BeginBatchDraw();
	change("�������");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("�������");

	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "������ı��:(��ʽ��001)");

	int w1 = textwidth("������ı��:(��ʽ��001)");
	int h1 = textheight("������ı��:(��ʽ��001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "����");
	mid_button(400, 450, "����");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//������
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
		MessageBox(NULL, "��Ų���Ϊ��", "����", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "�������������", "����", MB_OK);
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
		MessageBox(NULL, "δ���ҵ���δ������", "����", MB_OK);
		return;
	}

	//�ļ�����
	fstream re("Lendmessage.txt", ios::out | ios::app);
	re << vec[i].getname() << "��" << sys.wYear << "-" << sys.wMonth << "-" << sys.wDay << "-" << sys.wHour << ":" << sys.wMinute << "��" << l.U.Getname() << "���." << endl;//�˴��е�Uname���ƻ���ִ���
	vec[i].returned();
	re.close();

	MessageBox(NULL, "����ɹ�", "��ʾ", MB_OK);
}

void SearchBookPage_U()
{

	BeginBatchDraw();
	change("��ѯ�����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("��ѯ�����");

	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "������ı��:(��ʽ��001)");

	int w1 = textwidth("������ı��:(��ʽ��001)");
	int h1 = textheight("������ı��:(��ʽ��001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "����");
	mid_button(400, 450, "����");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//������
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
	change("��ѯ�����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("��ѯ�����");

	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "������ı��:(��ʽ��001)");

	int w1 = textwidth("������ı��:(��ʽ��001)");
	int h1 = textheight("������ı��:(��ʽ��001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "����");
	mid_button(400, 450, "����");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//������
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
		MessageBox(NULL, "��Ų���Ϊ��", "����", MB_OK);
		delete[] a;
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "�������������", "����", MB_OK);
		return;
	}

	bool found = false;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].getcode().c_str() << " " << number << " " << strcmp(vec[i].getcode().c_str(), number)<<endl;
		if (strcmp(vec[i].getcode().c_str(), number) == 0)
		{
			strcpy(a, ""); 
			strcat(a, "���: ");
			strcat(a, vec[i].getcode().c_str());
			strcat(a, "\n����: ");
			strcat(a, vec[i].getname().c_str());
			strcat(a, "\n����: ");
			strcat(a, vec[i].getauthor().c_str());
			strcat(a, "\n����: ");
			strcat(a, to_string(vec[i].getsum()).c_str());

			MessageBox(NULL, a, "�鼮��Ϣ", MB_OK);
			found = true;
			break; 
		}
	}

	delete[] a;

	if (!found)
	{
		MessageBox(NULL, "δ���ҵ�", "�鼮��Ϣ", MB_OK);
	}
}

void DeleteBookPage()
{
	BeginBatchDraw();
	change("ɾ�������");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("ɾ�������");

	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "��ɾ����ı��:(��ʽ��001)");

	int w1 = textwidth("��ɾ����ı��:(��ʽ��001)");
	int h1 = textheight("��ɾ����ı��:(��ʽ��001)");

	fillrectangle(300 + w1, 200, 700, 200 + h1);

	mid_button(325, 375, "ɾ��");
	mid_button(400, 450, "����");

	char* number = new char[28];
	number[0] = '\0';
	EndBatchDraw();

	//������
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
		MessageBox(NULL, "��Ų���Ϊ��", "����", MB_OK);
		return;
	}

	try {
		int codenum = stoi(number);
	}
	catch (const std::invalid_argument& e) {
		MessageBox(NULL, "�������������", "����", MB_OK);
		return;
	}

	vector<Book> va;
	vector<Book>::iterator it;
	Book b;
	fstream file("Bookmessage.txt", ios::binary | ios::in); //���ļ�
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
		MessageBox(NULL, "δ���ҵ�", "����", MB_OK);
		return;
	}

	fstream file1("Bookmessage.txt", ios::out | ios::trunc);
	for (int i = 0; i < va.size(); i++)
	{
		file1 << va[i].getcode() << " " << va[i].getname() << " " << va[i].getauthor() << " " << va[i].getsum() << endl;
		//��δɾ����ͼ��д���ļ�
	}
	file1.close();

	if (flag == 1) MessageBox(NULL, "ɾ���ɹ�", "��ʾ", MB_OK);
}

void AddBookPage()
{
	BeginBatchDraw();
	change("����鼮����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("����鼮����");

	//���ⰴť
	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "�鼮���:");
	outtextxy(300, 250, "�鼮����:");
	int w1 = textwidth("�鼮���:");
	int h1 = textheight("�鼮���:");

	int w2 = textwidth("����:");

	outtextxy(300 + w1 - w2, 300, "����:");
	outtextxy(300 + w1 - w2, 350, "����:");

	fillrectangle(300+w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);
	fillrectangle(300 + w1, 300, 700, 300 + h1);
	fillrectangle(300 + w1, 350, 700, 350 + h1);


	outtextxy(300, 400, "ע��!�鼮��Ÿ�ʽΪ001");

	mid_button(430, 480, "���");
	mid_button(500, 550, "����");

	EndBatchDraw();

	char* code = new char[28];
	code[0] = '\0';
	char* name = new char[28];
	name[0] = '\0';
	char* author = new char[28];
	author[0] = '\0';
	char* sum = new char[28];
	sum[0] = '\0';

	//������
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
		MessageBox(NULL, "��ȷ����д��������ȷ", "����", MB_OK);
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
		MessageBox(NULL, "�������������������", "����", MB_OK);
		return;
	}

	if (!check_code(code)) {
		MessageBox(NULL, "�鼮����ظ�", "����", MB_OK);
		return;
	}

	fstream bookmessage("Bookmessage.txt", ios::app);
	if (bookmessage.is_open())
	{
		bookmessage << B.getcode() << " " << B.getname() << " " << B.getauthor() << " " << B.getsum() << endl;
		MessageBox(NULL, "��ӳɹ�", "��ʾ", MB_OK);
		bookmessage.close();
	}
	else MessageBox(NULL, "�ļ���ʧ��", "����", MB_OK);
}

bool check_code(char* code)
{
	vector<Book> va;
	vector<Book>::iterator it;
	Book b;
	fstream file("Bookmessage.txt", ios::binary | ios::in); //���ļ�
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
	change("�û���¼����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("�û���¼����");

	//���ⰴť
	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "�û���:");
	int w1 = textwidth("�û���:");
	int h1 = textheight("�û���:");

	int w2 = textwidth("����:");
	int h2 = textheight("����:");

	outtextxy(300 + w1 - w2, 250, "����:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);


	mid_button(325, 375, "��¼");
	mid_button(400, 450, "����");


	setbkmode(TRANSPARENT);
	//������ʾ��ť,ʹ��ͼƬ���صķ�ʽ
	IMAGE img2;
	loadimage(&img2, "./�۾����ɼ�.jpg", 40, h1);
	putimage(710, 250, &img2);

	EndBatchDraw();



	//���ڼ������뱣����������ͳ�ʼ��
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	//������
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
	change("����Ա��¼����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("����Ա��¼����");

	//���ⰴť
	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "�û���:");
	int w1 = textwidth("�û���:");
	int h1 = textheight("�û���:");

	int w2 = textwidth("����:");
	int h2 = textheight("����:");

	outtextxy(300 + w1 - w2, 250, "����:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);


	mid_button(325, 375, "��¼");
	mid_button(400, 450, "����");

	EndBatchDraw();

	setbkmode(TRANSPARENT);
	//������ʾ��ť,ʹ��ͼƬ���صķ�ʽ
	IMAGE img2;
	loadimage(&img2, "./�۾����ɼ�.jpg", 40, h1);
	putimage(710, 250, &img2);
	EndBatchDraw();




	//���ڼ������뱣����������ͳ�ʼ��
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	//������
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

	change("�û�ע�����");
	//���ñ���
	cleardevice();
	IMAGE img;
	loadimage(&img, "./�ݵر���.jpg", 1000, 640);
	putimage(0, 0, &img);

	//�������
	title("�û�ע�����");

	//���ⰴť
	settextcolor(BLACK);
	settextstyle(30, 10, "΢���ź�");
	outtextxy(300, 200, "�û���:");
	int w1 = textwidth("�û���:");
	int h1 = textheight("�û���:");

	int w2 = textwidth("����:");
	int h2 = textheight("����:");

	int w3 = textwidth("���ٴ���������:");

	outtextxy(300 + w1 - w2, 250, "����:");
	outtextxy(300 + w1 - w3, 300, "���ٴ���������:");

	fillrectangle(300 + w1, 200, 700, 200 + h1);
	fillrectangle(300 + w1, 250, 700, 250 + h1);
	fillrectangle(300 + w1, 300, 700, 300 + h1);

	setbkmode(TRANSPARENT);
	//������ʾ��ť,ʹ��ͼƬ���صķ�ʽ
	IMAGE img2;
	loadimage(&img2, "./�۾����ɼ�.jpg", 40, h1);
	putimage(710, 250, &img2);
	IMAGE img3;
	loadimage(&img3, "./�۾����ɼ�.jpg", 40, h1);
	putimage(710, 300, &img2);


	mid_button(340, 390, "ע��");
	mid_button(400, 450, "����");

	EndBatchDraw();

	//���ڼ������뱣����������ͳ�ʼ��
	char* UserName = new char[28];
	UserName[0] = '\0';

	char* PassWord = new char[28];
	PassWord[0] = '\0';

	char* PassWord2 = new char[28];
	PassWord2[0] = '\0';

	//������
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
		MessageBox(NULL, "��ȷ����д��������ȷ", "����", MB_OK);
		return;
	}
	else if (strcmp(PassWord, PassWord2) != 0)
	{
		MessageBox(NULL, "����������д����ͬ", "����", MB_OK);
		return;
	}

	User U;

	U.SetID(UserName);
	U.Setname(UserName);
	U.SetKey(PassWord);
	fstream file("Usermessage.txt", ios::out | ios::app);
	file << " " << U.GetID() << " " << U.Getname() << " " << U.Getkey() << endl; //д���ļ�

	currentPage = PAGE_MAIN_MENU;
	MessageBox(NULL, "ע��ɹ�!", "��ʾ", MB_OK);
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

	// ���ݻ���ֵ
	int oldlinecolor = getlinecolor();
	int oldbkcolor = getbkcolor();
	int oldfillcolor = getfillcolor();

	setlinecolor(LIGHTGRAY);		// ���û�����ɫ
	setbkcolor(WHITE);			// ���ñ�����ɫ
	setfillcolor(WHITE);			// ���������ɫ

	//��ʼ��
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
						clearrectangle(left + width, top + 1, right - 1, bottom - 1);//���������
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

						//��������
						clearrectangle(left, top, left + 10 + width + 1, bottom);// ����֮ǰ������
						width = textwidth(text);
						counter = 0;
						outtextxy(left + 1, top + 1, text);
					}
					break;
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);
		}
		//���ƹ��(�����˸����Ϊ20ms*32)
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		else
			clearrectangle(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		Sleep(20);
	}

	clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����


	fillrectangle(left, top, right, bottom);
	outtextxy(left + 1, top + 1, text);



	// �ָ�����ֵ
	setlinecolor(oldlinecolor);
	setbkcolor(oldbkcolor);
	setfillcolor(oldfillcolor);
}

void passwordInput(int left, int right, int top, int bottom, char* text, ExMessage& msg)
{

	setlinecolor(LIGHTGRAY);		// ���û�����ɫ
	setbkcolor(WHITE);			// ���ñ�����ɫ
	setfillcolor(WHITE);			// ���������ɫ

	//��ʼ��
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
						clearrectangle(left + width, top + 1, right - 1, bottom - 1);//���������
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

						clearrectangle(left, top, left + 10 + width + 1, bottom);// ����֮ǰ������
						width = textwidth(mask);
						counter = 0;
						outtextxy(left + 1, top + 1, mask);
					}
					break;
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);
		}
		//���ƹ��(�����˸����Ϊ20ms*32)
		counter = (counter + 1) % 32;
		if (counter < 16)
			line(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		else
			clearrectangle(left + 4 + width, top + 3, left + 4 + width, bottom - 3);
		Sleep(20);
	}

	clearrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);	// �����


	fillrectangle(left, top, right, bottom);
	outtextxy(left + 1, top + 1, mask);




}

void passwordDisplay(int left, int right, int top, int bottom, char* text, ExMessage& msg)
{
	//��Ϊ�ɼ�
	IMAGE img2;
	loadimage(&img2, "./�۾��ɼ�.jpg", 40, 30);
	putimage(left,top, &img2);



	clearrectangle(365, top, 700, bottom);
	fillrectangle(365, top, 700, bottom);
	outtextxy(365 + 1, top + 1, text);

	//����׼��
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
					loadimage(&img2, "./�۾����ɼ�.jpg", 40, 30);
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
		MessageBox(NULL, "�û���������δ����", "����", MB_OKCANCEL);
	}
	else if (!l.checkUser(UserName, PassWord))
	{
		MessageBox(NULL, "�û����������������", "����", MB_OKCANCEL);
	}
	else if (l.checkUser(UserName, PassWord))
	{
		currentPage = PAGE_USER_MENU;
		MessageBox(NULL, "��¼�ɹ�", "��ʾ", MB_OKCANCEL);
		UserMenu();
	}
}

void LibrarianLoad(char* UserName, char* PassWord)
{
	if (UserName[0] == '\0' || PassWord[0] == '\0')
	{
		MessageBox(NULL, "�û���������δ����", "����", MB_OKCANCEL);
	}
	else if (!l.Librarian_log(UserName, PassWord))
	{
		MessageBox(NULL, "�û����������������", "����", MB_OKCANCEL);
	}
	else if (l.Librarian_log(UserName, PassWord))
	{
		currentPage = PAGE_LIBRARIAN_MENU;
		MessageBox(NULL, "��¼�ɹ�", "��ʾ", MB_OKCANCEL);
		LibrarianMenu();
	}
}