#include "stdafx.h"
using namespace std;
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
	setlocale( LC_ALL,"Russian" );
	int i=0;
	string s;
	char * buff=new char[1024];
	while (true)
	{
		getline(cin,s); 
		*(unsigned*)buff=LOGIN;
		communicator->Write(buff,1024);
		communicator->Read(buff);
		getline(cin,s); 
		*(unsigned*)buff=ENTER_WORLD;
		communicator->Write(buff,1024);
		communicator->Read(buff);
	}
	/*
	while(true)
	{
	getline(cin,s); 
	*(unsigned*)buff=VISIBLE_OBJECTS_NAME_LIST;
	communicator->Write(buff,1024);
	communicator->Read(buff);
	WCHAR * name;
	cout<<"OBJECTS COUNT "<<*(unsigned*)buff<<endl;
	for (int i=1;i<=*(unsigned*)buff;i++)
	{
	name=ReadStringUTF8((unsigned*)*(unsigned*)(buff+i*4),0);
	//wprintf(name);
	wcout<<name<<endl;
	//cout<<hex<<*(unsigned*)(buff+i*4)<<": "<<dec<<i<<endl;
	}
	}
	*/
	delete buff;
}
WCHAR * ProcessInteractor::ReadStringUTF8(void * address,DWORD length)
{
	wchar_t * tmpWCResult;
	wchar_t * tmpResult;
	wchar_t *result;
	MEMORY_BASIC_INFORMATION bi={0};
	VirtualQuery(address,&bi,sizeof(bi));
	DWORD real_length=0;
	DWORD resLength=0;
	if (length==0)
	{
		length=1024;
	}
	if (bi.RegionSize-((unsigned)address-(unsigned)bi.BaseAddress)>=length*2)
	{

		real_length=length;
	}
	else
	{
		real_length=(bi.RegionSize-((DWORD)address-(DWORD)bi.BaseAddress))/2;
	}
	tmpWCResult=new wchar_t[length];
	tmpResult=new wchar_t[length];


	if(!ReadProcessMemory(process_handle,address,tmpWCResult,real_length*2,NULL))
	{
		return NULL;
	}
	MultiByteToWideChar(65001,0,(LPCCH)tmpWCResult,-1,tmpResult,real_length);
	resLength=wcslen(tmpResult)+1;
	result=new wchar_t[resLength];
	memcpy(result,tmpResult,resLength*2);
	delete tmpWCResult;
	delete tmpResult;
	return result;
}
