#pragma once
typedef int (__cdecl *DefaultServerLogin)(int p);
typedef BOOL (__cdecl *pEnterWorld)();
typedef BOOL (__cdecl *pLastHardwareAction )(void * stamp);
typedef char (__cdecl* CGlueMgr__LoginServerLogin)(int p,char * login, char * password);
typedef void (__cdecl*pSignalEvent)(int eventId, const char *fmt, ...);




//typedef LoadWardenModule;
//typedef int (__cdecl * Framescript_ExecuteBuffer)();

class Client
{
	//static DefaultServerLogin  pDefaultServerLogin;
	static pEnterWorld fpEnterWorld;
	//static pLastHardwareAction fpLastHardwareAction;
	static CGlueMgr__LoginServerLogin fpLogin;
	static pSignalEvent fpSignalEvent;

public:
	Client(void);
	~Client(void);
	//static int ServerLogin(int p){return pDefaultServerLogin(p);}
	static BOOL EnterWorld() {return fpEnterWorld();}
	//static BOOL LastHardwareAction(void * stamp) {return fpLastHardwareAction(stamp);}
	static char Login(int p,char * login, char * password) {return fpLogin(p, login, password);}
	static void SignalEvent(int eventId, const char *fmt, ...){return fpSignalEvent(eventId,fmt);}
};


