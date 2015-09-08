#pragma once
#define MAX_BUFFER_SIZE 1024
//Interaction commands
#define VISIBLE_OBJECTS_LIST 10



class Communicator
{
	protected:
		HANDLE request;
		HANDLE response;
		HANDLE sc_started;
		WCHAR * name;
		HANDLE pipe;
		void GetPipeNameStr(WCHAR** buff,DWORD pid);
	public:
		Communicator(void);
		~Communicator(void);
		DWORD Read(char * buff);
		bool Write(char * buff, DWORD lenght);

	

};

