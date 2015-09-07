#include "stdafx.h"
#include <TlHelp32.h>
#include <Psapi.h>


ProcessDispatcher::ProcessDispatcher(void)
{
}


ProcessDispatcher::~ProcessDispatcher(void)
{
}
void ProcessDispatcher::ScanProcesses()
{

}
ProcessInteractor * ProcessDispatcher::CreateWowProcess()
{
	unsigned attempts_count=6;
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32={0};
	me32.dwSize = sizeof( MODULEENTRY32 );
	unsigned attempts=0;
	bool dxgi_dll_loaded=false;
	if (!CreateProcess(WOW_EXECUTABLE_PATH,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		throw ProcessCreationException(&(string)"CreateProcess" ,GetLastError());
	}
	attempts=0;
	do
	{
		Sleep(5000);
		hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pi.dwProcessId);
		if (hModuleSnap == INVALID_HANDLE_VALUE)
		{
			continue;
		}
		if( !Module32First( hModuleSnap, &me32 ) )
		{
			throw ProcessCreationException(&(string)"Cant find first module" ,GetLastError());
		}
		while (Module32Next(hModuleSnap,&me32))
		{
			if (wcscmp(me32.szModule,L"dxgi.dll")==0)
			{
				Sleep(10000);
				ProcessInteractor * interactor=new ProcessInteractor(pi.hProcess,pi.dwProcessId);
				interactor->InjectDLL();
				interactor->InitCommunicator();
				return interactor;
			}		
		}
		attempts++;

	}
	while (! dxgi_dll_loaded && attempts<10);
	throw ProcessCreationException(&(string)"Cant find modules" ,GetLastError());
}
ProcessInteractor * ProcessDispatcher::StartNewProcess()
{
	int count=0;
	ProcessInteractor * p=nullptr;
	while (p==NULL)
	{
		try
		{
			p= CreateWowProcess();
		}
		catch(...)
		{
			p->KillProcess();
			cout<<"OOPS!! "<<count<<endl;
			count++;
		}
	}
	return p;
}