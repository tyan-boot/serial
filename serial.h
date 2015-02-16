#include <windows.h>

class Serial
{
	public:
		bool ReadCom(char *read,int num = 1);
		bool WriteCom(char *write,int num = 1);
		bool openCom(char *COM);
		bool closeCom();
		bool setTimeOut(
				int ReadIntervalTimeout,		//�������ʱ
				int ReadTotalTimeoutMultiplier,		//��ʱ��ϵ��
				int ReadTotalTimeoutConstant,		//��ʱ�䳣��
				int WriteTotalTimeoutMultiplier,	//дʱ��ϵ��
				int WriteTotalTimeoutConstant		//дʱ�䳣��
				);
		bool setBCD(
			DWORD BaudRate,		//������
			DWORD fParity, 		// ָ����żУ��ʹ��
			BYTE ByteSize,		// ͨ���ֽ�λ����4��8
			BYTE Parity, 		//ָ����żУ�鷽�����˳�Ա����������ֵ��
			BYTE StopBits 		//ָ��ֹͣλ��λ����
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
