#include "stdafx.h"
#include "Communicator_Client.h"
#include<ctime>
Communicator_Client::Communicator_Client(DWORD pid):Communicator()
{
	pipe=NULL;
	GetPipeNameStr(&name,pid);
	unsigned attempts=0;
	do
	{
		Sleep(7000);
		pipe= CreateFile(name,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		attempts++;
	}while (pipe==INVALID_HANDLE_VALUE && attempts<4);
	if (pipe==NULL || pipe==INVALID_HANDLE_VALUE)
	{
		throw  CommunicatorException(&(string)"Cant create pipe", GetLastError());
	}
}


Communicator_Client::~Communicator_Client(void)
{
}

void Communicator_Client::ConnectionCheck()
{ 
	

}
