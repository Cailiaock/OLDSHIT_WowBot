#pragma once
class Exception: public exception
{
protected:
	char * message;
public:
	virtual const char* what() const throw()
	{
		return message;
	}
	Exception(string * text, DWORD error)
	{	
		string error_num_str=to_string((_Longlong)error);
		string mess=((*text)+". Error number "+error_num_str).c_str();
		mess=mess+".";
		message=new char [mess.length()+1];
		strcpy(message,mess.c_str());

	}
	~Exception()
	{
		if (message)
			delete message;
	}
};