//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2011 achellies (achellies at 163 dot com)
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#include "stdafx.h"
#include "..\DuiLib\Utils\WinImplBase.h"
#include "main_frame.hpp"
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

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	CPaintManagerUI::SetInstance(hInstance);

    HRESULT hr1 = Initialize(NULL, NULL); //frame init
    frame_SetInstancesManager(GetInstancesManager());

	MainFrame* pFrame = new MainFrame();
	if( pFrame == NULL ) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
	pFrame->Create(NULL, _T("MenuTest"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
#else
	pFrame->Create(NULL, _T("MenuTest"), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();

    HRESULT hr2 = Destory(); //frame uninit
	return 0;
}