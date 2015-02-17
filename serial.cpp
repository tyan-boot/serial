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
		std::cout<<"�򿪳ɹ�"<<std::endl;
	}else
	{
		std::cout<<"��ʧ��"<<std::endl;
	}

	SetupComm(com.hCom,1024,1024);

	com.setTimeOut(1000,500,5000,500,2000);
	com.setBCD(9600,0,8,NOPARITY,ONESTOPBIT);

	PurgeComm(com.hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	char tmp[1];

	if (com.ReadCom(tmp,1))
	{
		std::cout<<"��ȡ�ɹ�"<<std::endl;
	}else
	{
		std::cerr<<"��ȡʧ��"<<std::endl;
	}

	std::cout<<tmp[0]<<std::endl;

	std::cout<<com.num_of_input()<<std::endl;

	com.closeCom();
}
