#pragma once
#include <iostream>
#include <errno.h>
#include<string.h>
using namespace std;

inline void myerror(string msg, std::string file, int line)
{
    perror(msg.c_str());
    std::cout << "错误发生在: "<< file << " " << line << std::endl;
    exit(1);
}

