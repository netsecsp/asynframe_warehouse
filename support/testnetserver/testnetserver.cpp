/*****************************************************************************
Copyright (c) 2012 - 2032, All rights reserved.

Author: Shengqian Yang, netsecsp@hotmail.com, China, last updated 05/01/2022
http://asynframe.sf.net

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the
above copyright notice, this list of conditions
and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/
#include "stdafx.h"
#include <conio.h>

#include <frame/AsynNetwork.h>
#define AAPIDLL_USING

#ifdef  AAPIDLL_USING
#include <frame/asm/ITypedef_i.c>
#include <frame/asm/IAsynFrame_i.c>
#include <frame/asm/IAsynNetwork_i.c>
#endif
#include <wsipx.h>    //֧��IPX/SPX
#include "TcpEvent.h"
#include "UdpEvent.h"

#ifdef  AAPIDLL_USING
#ifdef _DEBUG
#pragma comment(lib, "asynsdk_mini-MDd.lib")
#else
#pragma comment(lib, "asynsdk_mini-MD.lib")
#endif
#pragma comment(lib,"asyncore_dll.lib")
#else
#pragma comment(lib,"asynframe_lib.lib")
#endif
STDAPI_(extern HRESULT) Initialize( /*[in ]*/IAsynMessageEvents *param1, /*[in ]*/IUnknown *param2 );
STDAPI_(extern HRESULT) Destory();
STDAPI_(extern InstancesManager *) GetInstancesManager();

int _tmain(int argc, _TCHAR *argv[])
{
    printf("usage: %s port tcp/udp|spx/ipx [host]\n\texample: %s 7675 tcp\n\n", argv[0], argv[0]);

    HRESULT hr1 = Initialize(NULL, NULL);

    do{
        InstancesManager *lpInstancesManager = GetInstancesManager();

        if( CHECK_NO(lpInstancesManager->Require(STRING_from_string(IN_AsynNetwork), 0)))
        {
            printf("can't load plugin: %s\n", IN_AsynNetwork);
            break;
        }

        CComPtr<IAsynNetwork     > spAsynNetwork;
        lpInstancesManager->GetInstance(STRING_from_string(IN_AsynNetwork), IID_IAsynNetwork, (IUnknown **)&spAsynNetwork);

        printf("\nlocalip:\n"); asynsdk::CStringVector ipvx(1);
        spAsynNetwork->EnumLocalAddress(0   ,&ipvx); for(int i = 0; i < ipvx.m_val.size(); ++ i) printf("%d: %s\n", i, ipvx.m_val[i].c_str()); printf("\n");

        printf("mac:\n"); ipvx.m_val.clear();
        spAsynNetwork->EnumLocalAddress(1<<8,&ipvx); for(int i = 0; i < ipvx.m_val.size(); ++ i) printf("%d: %s\n", i, ipvx.m_val[i].c_str()); printf("\n");

        printf("nid:\n"); ipvx.m_val.clear();
        spAsynNetwork->EnumLocalAddress(2<<8,&ipvx); for(int i = 0; i < ipvx.m_val.size(); ++ i) printf("%d: %s\n", i, ipvx.m_val[i].c_str()); printf("\n");

        printf("gateway:\n"); ipvx.m_val.clear();
        spAsynNetwork->EnumLocalAddress(4<<8,&ipvx); for(int i = 0; i < ipvx.m_val.size(); ++ i) printf("%d: %s\n", i, ipvx.m_val[i].c_str()); printf("\n");

        CComPtr<IAsynFrameThread > spAsynFrameThread;
        lpInstancesManager->NewInstance(0, 0, IID_IAsynFrameThread, (IUnknown **)&spAsynFrameThread);

        if( argc <= 2 || strcmp(argv[2], "tcp") == 0 )
        {
            CTcpEvent *pEvent = new CTcpEvent( spAsynFrameThread, spAsynNetwork, argc > 3 && (strlen(argv[3]) == 0 || strchr(argv[3], ':') != 0)? 23 : AF_INET );
            if( pEvent->Start(argc <= 1? 7675 : atoi(argv[1]), argc <= 3? "" : argv[3]) )
            {
                while( _kbhit() == 0 )
                {
                    Sleep(100);
                }
            }
            pEvent->Shutdown();
            delete pEvent;
        }
        else if( strcmp(argv[2], "udp") == 0 )
        {
            CUdpEvent *pEvent = new CUdpEvent( spAsynFrameThread, spAsynNetwork, argc > 3 && (strlen(argv[3]) == 0 || strchr(argv[3], ':') != 0)? 23 : AF_INET );
            if( pEvent->Start(argc <= 1? 7675 : atoi(argv[1]), argc <= 3? "" : argv[3], argc <= 4? 0 : argv[4]) )
            {
                while( _kbhit() == 0 )
                {
                    Sleep(100);
                }
            }
            pEvent->Shutdown();
            delete pEvent;
        }
        else if( strcmp(argv[2], "spx") == 0 )
        {
            CTcpEvent *pEvent = new CTcpEvent( spAsynFrameThread, spAsynNetwork, AF_IPX );
            if( pEvent->Start(argc <= 1? 7675 : atoi(argv[1]), argc <= 3? "" : argv[3]) )
            {
                while( _kbhit() == 0 )
                {
                    Sleep(100);
                }
            }
            pEvent->Shutdown();
            delete pEvent;
        }
        else if( strcmp(argv[2], "ipx") == 0 )
        {
            CUdpEvent *pEvent = new CUdpEvent( spAsynFrameThread, spAsynNetwork, AF_IPX );
            if( pEvent->Start(argc <= 1? 7675 : atoi(argv[1]), argc <= 3? "" : argv[3]) )
            {
                while( _kbhit() == 0 )
                {
                    Sleep(100);
                }
            }
            pEvent->Shutdown();
            delete pEvent;
        }
    }while(0);

    HRESULT hr2 = Destory();
    return 0;
}
