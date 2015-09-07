#include "stdafx.h"

ProcessInteractor::ProcessInteractor(HANDLE handle,DWORD pid)
{
	process_handle=handle;
	this->pid=pid;
}


ProcessInteractor::~ProcessInteractor(void)
{
}
void ProcessInteractor::InjectDLL()
{
	Sleep(5000);
	LPVOID remoteParamString=NULL;
	LPVOID LoadLibraryARemoteAddr=NULL;
	LoadLibraryARemoteAddr= GetProcAddress(GetModuleHandle(L"kernel32.dll"),"LoadLibraryA");
	if (LoadLibraryARemoteAddr==NULL)
	{
		throw ProcessInteractorException(&(string)"GetProcessAdress function failed",GetLastError());
	}
	remoteParamString=VirtualAllocEx(process_handle,NULL,strlen(DLL_PATH)+1,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (remoteParamString==NULL)
	{
		throw ProcessInteractorException(&(string)"VirtualAllocEx function failed",GetLastError());
		
	}
	if (!WriteProcessMemory(process_handle,remoteParamString,DLL_PATH,strlen(DLL_PATH)+1,NULL))
	{
		throw ProcessInteractorException(&(string)"WriteProcessMemory function failed",GetLastError());
	}
	if(!CreateRemoteThread(process_handle,NULL,NULL,(LPTHREAD_START_ROUTINE)LoadLibraryARemoteAddr,remoteParamString,0,NULL))
	{
		throw ProcessInteractorException(&(string)"CreateRemoteThread function failed",GetLastError());
	}
	
}
void ProcessInteractor::InitCommunicator()
{
	communicator=new Communicator_Client(pid);
}
void ProcessInteractor::KillProcess()
{
	if (process_handle!=INVALID_HANDLE_VALUE || process_handle==NULL)
		TerminateProcess(process_handle,0);
}
void ProcessInteractor::TestChat()
{
	char * buff=new char[1024];
	while(true)
	{
		cin>>buff;
		communicator->Write(buff,strlen(buff));
		communicator->Read(buff);
		cout<<buff<<endl;
	}
	delete buff;
}