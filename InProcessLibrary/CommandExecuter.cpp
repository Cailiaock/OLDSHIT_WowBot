#include "StdAfx.h"
#include "CommandExecuter.h"
#include <WinSock2.h>
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
		//*param[1]++;
		//param[2][*param[1]]=(unsigned)pObject;
		param->counter++;
		param->list[param->counter]=(unsigned)pObject;
		return TRUE;
	}
	return FALSE;
}
void CommandExecuter::Execute()
{
	if (got_command)
	{
		//memcpy(&command,command_buff,4);
		unsigned command=*(unsigned*)command_buff;
		switch(command)
		{
		case VISIBLE_OBJECTS_LIST:
			{
				Filter filter={0};
				filter.counter=0;
				filter.list=(unsigned*)command_buff;
				ObjectMgr::EnumVisibleObjects(ObjectsEnumProc,&filter);
				*(unsigned*)command_buff=filter.counter;
				break;
			}
		case 1:
			{
				strcpy(command_buff,"QQQQQQ");
				break;
			}

		}

		got_command=false;
		SetEvent(command_executed);
		
	}
}
void CommandExecuter::PushToExecute(char * buff)
{	
	if (!got_command)
	{
		command_buff=buff;
		got_command=true;
		ResetEvent(command_executed);
		WaitForSingleObject(command_executed,INFINITE);
		buff=command_buff;
		int i=10;
	}
}
