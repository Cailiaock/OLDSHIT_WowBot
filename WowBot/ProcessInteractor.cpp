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
	cout<<"Interactor: DLL injected, waiting for server communicator."<<endl;
	
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
	int i;
	cin>>i;
	char * buff=new char[1024];
	while(true)
	{

		//cin>>buff;
		*(unsigned*)buff=VISIBLE_OBJECTS_LIST;
		//command=htonl(command);
		//memcpy(buff,&command,4);
		communicator->Write(buff,1024);
		communicator->Read(buff);
		for (int i=0;i<*(unsigned*)buff;i++)
		{
			cout<<hex<<*(unsigned*)(buff+i+1)<<": "<<dec<<i<<endl;
		}
		//cout<<buff<<endl;
	}
	delete buff;
}
