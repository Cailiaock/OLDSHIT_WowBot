#pragma once
#include "stdafx.h"
static class CommandExecuter
{
	static bool got_command;
	static HANDLE command_executed;
	
	void ProcessCommand( char * buff);
public:
	static char * command_buff;
	CommandExecuter(void);
	~CommandExecuter(void);
	static void Execute();
	static void PushToExecute(char * buff);
	static void ProcessCommand();

};

