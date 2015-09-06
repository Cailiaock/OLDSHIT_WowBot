#include <Communicator.h>
#pragma once
class Communicator_Client: protected Communicator
{
public:
	Communicator_Client(DWORD pid);
	~Communicator_Client(void);
};

