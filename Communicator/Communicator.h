#pragma once
#define MAX_BUFFER_SIZE 1024
class Communicator
{
	protected:
		WCHAR * name;
		HANDLE pipe;
		void GetPipeNameStr(WCHAR** buff,DWORD pid);
	public:
		Communicator(void);
		~Communicator(void);
		bool Read(char * buff);
		bool Write(char * buff, DWORD lenght);

	

};

