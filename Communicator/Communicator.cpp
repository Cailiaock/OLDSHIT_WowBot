#include "stdafx.h"
#include "Communicator.h"

Communicator::Communicator(void)
{
	request=CreateEvent(NULL,TRUE,FALSE,L"write");
	response=CreateEvent(NULL,TRUE,FALSE,L"read");
	sc_started=CreateEvent(NULL,TRUE,FALSE,L"server_started");
}


Communicator::~Communicator(void)
{
	CloseHandle(request);
	CloseHandle(response);
	CloseHandle(sc_started);
	CloseHandle(pipe);
}
DWORD Communicator::Read(char * buff)
{
	WaitForSingleObject(request,INFINITE);
	DWORD bytesRead=0;
	if (ReadFile(pipe,buff,MAX_BUFFER_SIZE,&bytesRead,NULL))
	{
		SetEvent(response);
		return bytesRead;
	}
	return 0;
}
bool Communicator::Write(char * buff, DWORD lenght)
{
	DWORD bytesWritten;
	SetEvent(request);
	if (WriteFile(pipe,buff,lenght,&bytesWritten,NULL))
	{
		WaitForSingleObject(response,INFINITE);
		return true;
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