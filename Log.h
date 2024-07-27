#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Librarian.h"
using namespace std;
class Log
{
    bool is_success;

public:
    User U;
    Librarian L;
    Log();
    ~Log();
    bool checkUser(char* UserName, char* Password);

    bool Librarian_log(char* UserName, char* PassWord);

    bool Is_success();
};
#endif