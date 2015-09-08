#include "stdafx.h"
#include "Communicator_Client.h"
#include<ctime>
Communicator_Client::Communicator_Client(DWORD pid):Communicator()
{
	pipe=NULL;
	GetPipeNameStr(&name,pid);
	unsigned attempts=0;
	WaitForSingleObject(sc_started,10000);
	pipe= CreateFile(name,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (pipe==NULL || pipe==INVALID_HANDLE_VALUE)
	{
		throw  CommunicatorException(&(string)"Cant create pipe", GetLastError());
	}
	cout<<"Communicator: Pipe created."<<endl;
}


Communicator_Client::~Communicator_Client(void)
{

}

void Communicator_Client::ConnectionCheck()
{ 
	

}
