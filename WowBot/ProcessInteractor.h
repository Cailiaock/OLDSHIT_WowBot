#pragma once
#include "stdafx.h"

class ProcessInteractorException: public Exception
{
public:
	ProcessInteractorException(string * text, DWORD error):Exception(text,error){};
};

class ProcessInteractor
{
	HANDLE process_handle;
	DWORD pid;
	Communicator * communicator;
	WCHAR * ReadStringUTF8(void * address,DWORD length);
public:
	ProcessInteractor(){}
	ProcessInteractor(HANDLE handle,DWORD pid);
	~ProcessInteractor(void);
	void InjectDLL();
	void InitCommunicator();
	void KillProcess();
	void TestChat();
	Communicator* GetCommunicator()
	{
		return communicator;
	}
};

