#include "stdafx.h"


Communicator::Communicator(void)
{

}


Communicator::~Communicator(void)
{
}
bool Communicator::Read(char * buff)
{
	DWORD bytesRead=0;
	if (ReadFile(pipe,buff,MAX_BUFFER_SIZE,&bytesRead,NULL))
	{
		if (*(DWORD*)buff==bytesRead)
		{
			return true;
		}
	}
	return false;
}
bool Communicator::Write(char * buff, DWORD lenght)
{
	DWORD bytesWritten;
	if (WriteFile(pipe,buff,lenght,&bytesWritten,NULL))
	{
		if (*(DWORD*)buff==bytesWritten)
		{
			return true;
		}
	}
	return false;
}
void Communicator::GetPipeNameStr(WCHAR ** buff,DWORD pid)
{
	WCHAR path[10];
	WCHAR  pid_str[10];
	wcscpy(path,L"\\\\.\\pipe\\");
	_itow(pid,pid_str,10);
	*buff=new WCHAR[20];
	wcscpy(*buff,path);
	wcscpy(*buff+9,pid_str);
}