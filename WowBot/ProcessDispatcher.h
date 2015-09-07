#pragma once
#include "stdafx.h"

class ProcessCreationException: public Exception
{ 
	
public:
	ProcessCreationException(string * text, DWORD error):Exception(text,error){};
};


class ProcessDispatcher
{
	vector <Communicator*> communicators;
public:
	vector<int*> *c; 
	ProcessDispatcher(void);
	~ProcessDispatcher(void);
	void ScanProcesses();
	ProcessInteractor * CreateWowProcess();
	ProcessInteractor * StartNewProcess();


};

