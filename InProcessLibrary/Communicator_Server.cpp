#include "stdafx.h"
#include "Communicator_Server.h"

Communicator_Server::Communicator_Server():Communicator()
{
	GetPipeNameStr(&name,GetCurrentProcessId());
	pipe=CreateNamedPipe(name,PIPE_ACCESS_DUPLEX,PIPE_TYPE_MESSAGE,PIPE_UNLIMITED_INSTANCES, 1024,1024,5000,NULL);
	if (pipe!=INVALID_HANDLE_VALUE && pipe!= NULL)
	{
		SetEvent(sc_started);
	}


}
Communicator_Server::~Communicator_Server()
{
}
