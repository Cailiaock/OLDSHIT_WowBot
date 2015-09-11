#include "StdAfx.h"
#include "CommandExecuter.h"
bool CommandExecuter::got_command=false;
char * CommandExecuter::command_buff=0;
HANDLE CommandExecuter::command_executed= CreateEvent(NULL,TRUE,FALSE,L"command_executed");
CommandExecuter::CommandExecuter(void)
{
}


CommandExecuter::~CommandExecuter(void)
{
	delete command_buff;
}
BOOL ObjectsEnumProc(CGObject_C * pObject, Filter * param)
{
	if (pObject)
	{   
		unsigned field_address;
		switch(param->param)
		{
		case 0:
			{
				field_address=(unsigned)pObject;
				break;
			}
		case 1:
			{
				field_address=(unsigned)pObject->GetObjectName();
				break;
			}
		}
		param->counter++;
		param->list[param->counter]=field_address;
		//unsigned o=(unsigned)pObject;
		//unsigned n=(unsigned)pObject->GetObjectName();
		return TRUE;
	}
	return FALSE;
}
void CommandExecuter::Execute()
{
	if (got_command)
	{
		got_command=false;
		unsigned command=*(unsigned*)command_buff;
		switch(command)
		{
		case VISIBLE_OBJECTS_LIST:
			{
				Filter filter={0};
				filter.param=0;
				filter.counter=0;
				filter.list=(unsigned*)command_buff;
				ObjectMgr::EnumVisibleObjects(ObjectsEnumProc,&filter);
				*(unsigned*)command_buff=filter.counter;
				break;
			}
		case VISIBLE_OBJECTS_NAME_LIST:
			{
				Filter filter={0};
				filter.param=1;
				filter.counter=0;
				filter.list=(unsigned*)command_buff;
				ObjectMgr::EnumVisibleObjects(ObjectsEnumProc,&filter);
				*(unsigned*)command_buff=filter.counter;
				break;
			}
		case LOGIN:
			{
				//Client::Login(0,"lissek7@ya.ru","lebmat2762066");
				//Client::Login(0,"arttambel@gmail.com","archi911");
				//unsigned m1=(unsigned)(GetModuleHandle(NULL)+0x12F4);
				//unsigned * m2=(unsigned*)(GetModuleHandle(NULL)+0x12F4);
				unsigned * baseframe=(unsigned*)*(unsigned*)((unsigned)(GetModuleHandle(NULL)+0x12F4));
				unsigned *current = (unsigned*)((unsigned)baseframe+0xD1A25C);
				WCHAR *  name = (WCHAR*)(unsigned)current+0x1C;
				
				break;
			}
		case ENTER_WORLD:
			{
				Client::EnterWorld();
				break;
			}
		}
		//got_command=false;
		SetEvent(command_executed);
		
		
		
	}
}
void CommandExecuter::PushToExecute(char * buff)
{	
	if (!got_command)
	{
		command_buff=buff;
		got_command=true;
		WaitForSingleObject(command_executed,INFINITE);
		buff=command_buff;
		int i=10;
	}
}
