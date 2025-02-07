#include "souistd.h"
#include "core/SMsgLoop.h"

#include "core/frame_Api.h"
#include <frame/asm/IAsynFrame_i.c>
extern InstancesManager *_g_lpInstancesManager;

namespace SOUI
{
    void SMessageLoop::OnMsg(LPMSG pMsg)
    {
        if(!PreTranslateMessage(pMsg))
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
        }
    }

	void SMessageLoop::Quit()
	{
		if (!m_bRunning) return;
		m_bQuit = TRUE;
	}

    int SMessageLoop::Run()
    {
        BOOL bDoIdle = TRUE;
        int nIdleCount = 0;
        BOOL bRet;
        
        m_bRunning = TRUE;
		m_bQuit = FALSE;

        if(_g_lpInstancesManager != 0 )
        {
            return Run_frame();
        }

        for(;;)
        {
            while(bDoIdle && !::PeekMessage(&m_msg, NULL, 0, 0, PM_NOREMOVE))
            {
                if(!OnIdle(nIdleCount++))
                    bDoIdle = FALSE;
				if (m_bQuit) goto exit_loop;
            }

            bRet = ::GetMessage(&m_msg, NULL, 0, 0);

            if(bRet == -1)
            {
				SLOGFMTD(_T("::GetMessage returned -1 (error)"));
                continue;   // error, don't process
            }
            else if(!bRet)
            {
				SLOGFMTD(_T("SMessageLoop::Run - exiting,code = %d"),(int)m_msg.wParam);
                break;   // WM_QUIT, exit message loop
            }
            
            OnMsg(&m_msg);

            if(IsIdleMessage(&m_msg))
            {
                bDoIdle = TRUE;
                nIdleCount = 0;
            }
			if (m_bQuit) break;
        }

	exit_loop:
        m_bRunning = FALSE;
        
        return (int)m_msg.wParam;
    }

    int SMessageLoop::Run_frame()
    {
        #pragma pack(push, 1)
        struct FRAMEMSG //for IThreadMessagePump.WaitMessage
        {
            uint32_t type; //消息类型: 0-定时器 1-异步消息 2-窗口消息
            void    *data;
        };
        #pragma pack(pop)

        IThreadMessagePump *lpThreadMessagePump;
        _g_lpInstancesManager->NewInstance(0, 2/*TC_Windows*/, IID_IThreadMessagePump, (IUnknown**)&lpThreadMessagePump);

        // for tracking the idle time state
        int nIdleCount = 0;
        FRAMEMSG msg;

        // acquire and dispatch messages until a WM_QUIT message is received.
        for(;;)
        {
            HRESULT ret = lpThreadMessagePump->WaitMessage(0, 5000/*5ms*/, (handle)&msg);
            if( ret == E_ABORT )
            {
                m_bQuit = TRUE;
                break;
            }

            if( ret == S_OK    ) 
            {
                if( msg.type == 2 ) 
                {// 2-窗口消息
                    OnMsg((MSG*)msg.data);
                    if(!IsIdleMessage((MSG*)msg.data))
                    {
                        nIdleCount = 0;
                    }
                }
                else
                {
                    lpThreadMessagePump->PumpMessage(0);
                    nIdleCount = 0;
                }
            } 
            else
            {
                // call OnIdle while in bIdle state
                OnIdle(nIdleCount ++);
            }
        }

        lpThreadMessagePump->Release();
        m_bRunning = FALSE;
        return 0;
    }

    BOOL SMessageLoop::OnIdle( int /*nIdleCount*/ )
    {
        for(size_t i = 0; i < m_aIdleHandler.GetCount(); i++)
        {
            IIdleHandler* pIdleHandler = m_aIdleHandler[i];
            if(pIdleHandler != NULL)
                pIdleHandler->OnIdle();
        }
        return FALSE;   // don't continue
    }

    BOOL SMessageLoop::PreTranslateMessage( MSG* pMsg )
    {
        // loop backwards
        for(int i = (int)m_aMsgFilter.GetCount() - 1; i >= 0; i--)
        {
            IMessageFilter* pMessageFilter = m_aMsgFilter[i];
            if(pMessageFilter != NULL && pMessageFilter->PreTranslateMessage(pMsg))
                return TRUE;
        }
        return FALSE;   // not translated
    }

    BOOL SMessageLoop::IsIdleMessage( MSG* pMsg )
    {
        // These messages should NOT cause idle processing
        switch(pMsg->message)
        {
        case WM_MOUSEMOVE:
        case WM_NCMOUSEMOVE:
        case WM_PAINT:
        case WM_SYSTIMER:	// WM_SYSTIMER (caret blink)
            return FALSE;
        }

        return TRUE;
    }

    BOOL SMessageLoop::RemoveIdleHandler( IIdleHandler* pIdleHandler )
    {
        return RemoveElementFromArray(m_aIdleHandler,pIdleHandler);
    }

    BOOL SMessageLoop::AddIdleHandler( IIdleHandler* pIdleHandler )
    {
        m_aIdleHandler.Add(pIdleHandler);
		return TRUE;
    }

    BOOL SMessageLoop::RemoveMessageFilter( IMessageFilter* pMessageFilter )
    {
        return RemoveElementFromArray(m_aMsgFilter,pMessageFilter);
    }

    BOOL SMessageLoop::AddMessageFilter( IMessageFilter* pMessageFilter )
    {
        m_aMsgFilter.Add(pMessageFilter);
		return TRUE;
    }


}//end of namespace SOUI
