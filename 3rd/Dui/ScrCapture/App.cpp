// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ScrCaptureWnd.h"
#include "..\DuiLib\Core\frame_Api.h"

#define AAPIDLL_USING

#ifdef AAPIDLL_USING
#pragma comment(lib, "asyncore_dll.lib")
#ifdef _DEBUG
#ifdef _DLL
#pragma comment(lib, "asynsdk_mini-MDd.lib")
#else
#pragma comment(lib, "asynsdk_mini-MTd.lib")
#endif
#else //
#ifdef _DLL
#pragma comment(lib, "asynsdk_mini-MD.lib")
#else
#pragma comment(lib, "asynsdk_mini-MT.lib")
#endif
#endif
#else
#ifdef _DLL
#pragma comment(lib, "asynframe-MD_lib.lib")
#else
#pragma comment(lib, "asynframe-MT_lib.lib")
#endif
#endif

STDAPI_(extern HRESULT) Initialize( /*[in ]*/IAsynMessageEvents *param1, /*[in ]*/IUnknown *param2 );
STDAPI_(extern HRESULT) Destory();
STDAPI_(extern InstancesManager *) GetInstancesManager();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

    HRESULT hr1 = Initialize(NULL, NULL); //frame init
    frame_SetInstancesManager(GetInstancesManager());

    CScrCaptureWnd* pFrame = CScrCaptureWnd::Instance();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T(""), WS_VISIBLE | WS_POPUP, /*WS_EX_TOOLWINDOW|WS_EX_TOPMOST*/0);
	pFrame->ShowWindow(true);
    
    CPaintManagerUI::MessageLoop();

    HRESULT hr2 = Destory(); //frame uninit
    return 0;
}
