#include "StdAfx.h"
#include "Client.h"

//int  (__cdecl *Client::pDefaultServerLogin)(int p)=reinterpret_cast<DefaultServerLogin>((unsigned)GetModuleHandle(NULL)+0x2027CF);
BOOL (__cdecl *Client::fpEnterWorld)()=reinterpret_cast<pEnterWorld>((unsigned)GetModuleHandle(NULL)+0x201E24);
//BOOL (__cdecl *Client::fpLastHardwareAction)(void * stamp)=reinterpret_cast<pLastHardwareAction>((unsigned)GetModuleHandle(NULL)+0xD1A258);
char (__cdecl *Client::fpLogin)(int p,char * login, char * password)=reinterpret_cast<CGlueMgr__LoginServerLogin>((unsigned)GetModuleHandle(NULL)+0x1F38F7);
void (__cdecl *Client::fpSignalEvent)(int eventId, const char *fmt, ...)=reinterpret_cast<pSignalEvent>((unsigned)GetModuleHandle(NULL)+0x2AC6B);
Client::Client(void)
{
}


Client::~Client(void)
{
}
