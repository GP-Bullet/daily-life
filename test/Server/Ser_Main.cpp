#include"Ser_ppool.h"
#include"Ser_ppool.cpp"
#include"Ser_Ok.hpp"


int main(int argc,char*argv[]){
    Server* ser=new Server();
    ser->ServerCtl();
    return 0;
}