#pragma once
#include "stdafx.h"
class CommunicatorException: public Exception
{ 
	
public:
	CommunicatorException(string * text, DWORD error):Exception(text, error){};
};

class Communicator_Client: public  Communicator
{
public:
	Communicator_Client(DWORD pid);
	~Communicator_Client(void);
	void ConnectionCheck();
};

