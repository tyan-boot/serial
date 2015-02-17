#include "serial.h"
#include <iostream>

int main(int argc,char **argv)
{
	const char *COM;
	if (argc <1)
	{
		COM = "COM1";
	}else
	{
		COM = argv[1];
	}

	Serial com;
	
	if (com.openCom((char*)COM))
	{
		std::cout<<"打开成功"<<std::endl;
	}else
	{
		std::cout<<"打开失败"<<std::endl;
	}

	SetupComm(com.hCom,1024,1024);

	com.setTimeOut(1000,500,5000,500,2000);
	com.setBCD(9600,0,8,NOPARITY,ONESTOPBIT);

	PurgeComm(com.hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	char tmp[1];

	if (com.ReadCom(tmp,1))
	{
		std::cout<<"读取成功"<<std::endl;
	}else
	{
		std::cerr<<"读取失败"<<std::endl;
	}

	std::cout<<tmp[0]<<std::endl;

	std::cout<<com.num_of_input()<<std::endl;

	com.closeCom();
}
