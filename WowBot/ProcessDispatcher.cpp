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
	PROCESS_INFORMATION pi = {0};
	STARTUPINFO si = {0};
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32={0};
	me32.dwSize = sizeof( MODULEENTRY32 );
	if (!CreateProcess(WOW_EXECUTABLE_PATH,NULL,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi))
	{
		throw ProcessCreationException(&(string)"CreateProcess" ,GetLastError());
	}
	cout<<"Wow.exe launched."<<endl;
	Sleep(30000);
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pi.dwProcessId);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		throw ProcessCreationException(&(string)"Invalid snapshot" ,GetLastError());
	}
	if( !Module32First( hModuleSnap, &me32 ) )
	{
		throw ProcessCreationException(&(string)"Cant find first module" ,GetLastError());
	}
	while (Module32Next(hModuleSnap,&me32))
	{
		if (wcscmp(me32.szModule,L"dxgi.dll")==0)
		{
			ProcessInteractor * interactor=new ProcessInteractor(pi.hProcess,pi.dwProcessId);
			interactor->InjectDLL();
			interactor->InitCommunicator();
			return interactor;
		}		
	}


	throw ProcessCreationException(&(string)"Cant find modules" ,GetLastError());
}
