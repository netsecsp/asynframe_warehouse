// RichListDemo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include "RichListWnd.h"
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
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\\skin"));
	//CPaintManagerUI::SetResourceZip(_T("RichListRes.zip"));

    HRESULT hr1 = Initialize(NULL, NULL); //frame init
    frame_SetInstancesManager(GetInstancesManager());

	CRichListWnd* pFrame = new CRichListWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("DuiLib Demo from mbstudio.cn / meineson"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 500, 400);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	//::MessageBox(NULL, _T("alert!"), _T("Duilib Demo"), MB_OK);

	CPaintManagerUI::MessageLoop();

    HRESULT hr2 = Destory(); //frame uninit
	return 0;
}
