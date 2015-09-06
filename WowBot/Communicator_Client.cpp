#include "stdafx.h"
#include "Communicator_Client.h"


Communicator_Client::Communicator_Client(DWORD pid)
{
	GetPipeNameStr(&name,pid);
	pipe= CreateFile(name,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}


Communicator_Client::~Communicator_Client(void)
{
}
