#include <windows.h>

class Serial
{
	public:
		bool ReadCom(char *read,int num = 1);
		bool WriteCom(char *write,int num = 1);
		bool openCom(char *COM);
		bool closeCom();
		bool setTimeOut(
				int ReadIntervalTimeout,		//读间隔超时
				int ReadTotalTimeoutMultiplier,		//读时间系数
				int ReadTotalTimeoutConstant,		//读时间常量
				int WriteTotalTimeoutMultiplier,	//写时间系数
				int WriteTotalTimeoutConstant		//写时间常量
				);
		bool setBCD(
			DWORD BaudRate,		//波特率
			DWORD fParity, 		// 指定奇偶校验使能
			BYTE ByteSize,		// 通信字节位数，4—8
			BYTE Parity, 		//指定奇偶校验方法。此成员可以有下列值：
			BYTE StopBits 		//指定停止位的位数。
			);	
		
		int num_of_input();

		HANDLE hCom;

	private:
		COMMTIMEOUTS TimeOuts;
		DCB dcb;
		COMSTAT comstat;

};

int Serial::num_of_input()
{
	DWORD Error;
	ClearCommError(this->hCom,&Error,&this->comstat);
	return this->comstat.cbInQue;
}

bool Serial::setBCD(DWORD BaudRate,DWORD fParity,BYTE ByteSize,BYTE Parity,BYTE StopBits)
{
	this->dcb.BaudRate = BaudRate;
	this->dcb.fParity = fParity;
	this->dcb.ByteSize = ByteSize;
	this->dcb.Parity = Parity;
	this->dcb.StopBits = StopBits;

	SetCommState(this->hCom,&this->dcb);
}

bool Serial::setTimeOut(int ReadIntervalTimeout,int ReadTotalTimeoutMultiplier,int ReadTotalTimeoutConstant,int WriteTotalTimeoutMultiplier,int WriteTotalTimeoutConstant)
{
	this->TimeOuts.ReadIntervalTimeout = ReadIntervalTimeout;
	this->TimeOuts.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;
	this->TimeOuts.ReadTotalTimeoutConstant	= ReadTotalTimeoutConstant;
	this->TimeOuts.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;
	this->TimeOuts.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;
	SetCommTimeouts(this->hCom,&this->TimeOuts);
}

bool Serial::openCom(char *COM)
{
	this->hCom = CreateFile(COM,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

	if (this->hCom == (HANDLE) - 1)
	{
		return false;
	}else return true;

}

bool Serial::closeCom()
{
	CloseHandle(this->hCom);
}

bool Serial::ReadCom(char *read,int num)
{	
	DWORD rCount;
	bool ComRead;

	ComRead = ReadFile(this->hCom,read,num,&rCount,NULL);

	if (!ComRead)
	{
		return false;
	}else
	{
		return true;
	}
}

bool Serial::WriteCom(char *write,int num)
{
	DWORD wCount;
	bool ComWrite;

	ComWrite = WriteFile(this->hCom,write,num,&wCount,NULL);

	if (!ComWrite)
	{
		return false;
	}else
	{
		return true;
	}
}
