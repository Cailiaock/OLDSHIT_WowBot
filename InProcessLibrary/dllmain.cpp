// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"
#include <d3d11.h>

#include <string>
#include "Communicator_Server.h"

using namespace std;

//BOOL enum_vo(CGObject_C * pObject, void *data);


HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*           g_pd3dDevice = NULL;
ID3D11DeviceContext*    g_pImmediateContext = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D11RenderTargetView* g_pRenderTargetView = NULL;

bool first_time=true;
unsigned * present_address=0;
LPVOID old_present_code;
IDXGISwapChain* chain;
typedef HRESULT (__stdcall *PresentPtr) (IDXGISwapChain* swap_chain,UINT SyncInterval,UINT Flags );

PresentPtr  old_present;
Communicator * c;

HRESULT __stdcall   Present(IDXGISwapChain * swap_chain,  UINT SyncInterval, UINT Flags)
{	
	if (first_time)
	{
		unsigned * vtable =*(unsigned**)swap_chain;
		unsigned * present_addr=vtable+8;
		unsigned  old_present_address=*present_addr;
		unsigned long old_protect=0;
		VirtualProtect(present_addr,4,PAGE_READWRITE,&old_protect);
		*present_addr=(unsigned)Present;
		VirtualProtect(present_addr,4,old_protect,&old_protect);
		VirtualProtect((void*)old_present_address,0x2F,PAGE_READWRITE,&old_protect);
		memcpy((void*)old_present_address,old_present_code,0x2F);
		VirtualProtect((void*)old_present_address,0x2F,old_protect,&old_protect);
		old_present=reinterpret_cast<PresentPtr>(old_present_address);
		first_time=false;
		c=new Communicator_Server();
		Sleep(1000);
		//DebugBreak();
	}
	//DebugBreak();

	//unsigned  * p = (unsigned*)ObjectMgr::GetActivePlayerGuid;

	//ObjectMgr::EnumVisibleObjects(enum_vo,NULL);
	char b[1024];
	c->Read(b);
	if (strcmp(b,"GREETING")==0)
		c->Write("RESPONSEGREETING",17);
	else 
		c->Write("HELLO",6);
	
	return old_present(swap_chain,SyncInterval,Flags);
}
/*
BOOL enum_vo(CGObject_C * pObject, void *data)
{
	cout<<pObject;
	const char * name=pObject->GetObjectName();
	return TRUE;
}
*/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			 unsigned long old_protect=0;
			 HMODULE hMod = GetModuleHandle(L"dxgi.dll");
			 old_present_code=VirtualAlloc(NULL,0x2F,MEM_COMMIT ,PAGE_READWRITE);
			 present_address=(unsigned*)((unsigned)hMod+0x2D7B9);
			 memcpy(old_present_code,present_address,0x2F);
			 VirtualProtect(old_present_code,0x2F,PAGE_EXECUTE_READ,&old_protect);
			 char * patch=new char[0x7];
			 patch[0]=0xB8;
			 unsigned p_ptr=((unsigned)Present);
			 memcpy(patch+1,&p_ptr,4);
			 patch[5]=0xFF;
			 patch[6]=0xE0;
			 VirtualProtect(present_address,0x7,PAGE_READWRITE,&old_protect);
			 memcpy(present_address,patch,0x7);
			 VirtualProtect(present_address,0x7,old_protect,&old_protect);
			 break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

