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
#pragma once

#define PER_DATA_SIZE 1500

class CTcpEvent : public asynsdk::asyn_message_events_impl
{
public:
    CTcpEvent(IAsynNetwork *lpAsynNetwork, IAsynFrameThread *lpAsynFrameThread, uint32_t af)
        : m_lSeqno(1), m_af(af)
    {
        m_spAsynFrameThread = lpAsynFrameThread;
        m_spAsynNetwork     = lpAsynNetwork;
        CreateAsynFrame(m_spAsynFrameThread, 0, &m_spAsynFrame);
    }

public:
    STDMETHOD(OnMessage)( /*[in]*/uint32_t lMessageId, /*[in]*/uint64_t lParam1, /*[in]*/uint64_t lParam2, /*[in]*/IUnknown **objects )
    {
        if( lMessageId != AF_IOMSG_NOTIFY )
        {
            printf("lMsg: %d, param: %I64d/%I64d\n", lMessageId, lParam1, lParam2);
        }
        if( lMessageId == AF_QUERY_RESULT )
        {
            if( lParam1 == 0 )
            {
                asynsdk::CStringSetter d(1);
                asynsdk::CMemorySetter c(1);
                ((IKeyvalSetter*)objects[0])->Get(STRING_from_string(";dattype"), 0, 0, &d);
                ((IKeyvalSetter*)objects[0])->Get(STRING_from_string(";context"), 0, 0, &c);
                if( d.m_val.rfind("cert.verify") != std::string::npos )
                {// cert.verify
                    ISsl *pSsl = (ISsl*)lParam2;
                    if( c.m_val.ptr )
                        return pSsl->VerifyPeerCertificate(*(handle*)c.m_val.ptr, 0x1000);
                    else
                        return S_OK; //no cert
                }
            }
            return E_NOTIMPL;
        }
        if( lMessageId == AF_IOMSG_NOTIFY )
        {
            IAsynIoOperation *lpAsynIoOperation = (IAsynIoOperation *)objects[0];
            uint32_t lErrorCode, lTransferedBytes;
            lpAsynIoOperation->GetCompletedResult(&lErrorCode, &lTransferedBytes, 0);

            if( lParam2 == Io_recv )
            {
                if( lErrorCode )
                {
                    printf("recv, error: %d\n", lErrorCode);
                    m_arOp2AsynTcpSockets.erase(lpAsynIoOperation);
                    return E_NOTIMPL;
                }
                else
                {
                    unsigned char *lpBuffer;
                    lpAsynIoOperation->GetIoBuffer(0, 0, &lpBuffer );
                    printf("recv[%4d] %s\n", lTransferedBytes, (char *)lpBuffer);

                    lpAsynIoOperation->SetIoParams(0, 10, 0);
                    return m_arOp2AsynTcpSockets[lpAsynIoOperation]->Read(lpAsynIoOperation);
                }
            }
            if( lParam2 == Io_send )
            {
                if( lErrorCode )
                {
                    printf("send, error: %d\n", lErrorCode);
                    m_arOp2AsynTcpSockets.erase(lpAsynIoOperation);
                    return E_NOTIMPL;
                }
                else
                {
                    if( m_lSeqno > 10 )
                    {
                        m_arOp2AsynTcpSockets.erase(lpAsynIoOperation);
                        return E_NOTIMPL;
                    }

                    unsigned char *lpBuffer;
                    lpAsynIoOperation->GetIoBuffer(0, 0, &lpBuffer);

                    sprintf_s((char *)lpBuffer, 10, "1%08d", m_lSeqno ++);
                    lpAsynIoOperation->SetIoParams(0, 10, 0);
                    return m_arOp2AsynTcpSockets[lpAsynIoOperation]->Write(lpAsynIoOperation);
                }
            }

            if( lParam2 == Io_acceptd )
            {
                if( lErrorCode )
                {
                    printf("accept, error: %d\n", lErrorCode);
                    return m_spAsynTcpSocketListener->Accept(lpAsynIoOperation);
                }

                m_lSeqno = 1;
                {
                    CComPtr<IAsynNetIoOperation> spAsynIoOperation;
                    lpAsynIoOperation->QueryInterface(IID_IAsynNetIoOperation, (void **)&spAsynIoOperation);
                    asynsdk::CStringSetter host;
                    PORT        port;
                    spAsynIoOperation->GetPeerAddress(&host, 0, &port, 0);
                    printf("succ to accept from %s:%d\n", host.m_val.c_str(), port);
                }

                CComPtr<IAsynTcpSocket     > spNewAsynTcpSocket;
                lpAsynIoOperation->GetCompletedObject(TRUE, IID_IAsynTcpSocket, (IUnknown **)&spNewAsynTcpSocket);

                {
                    //send
                    CComPtr<IAsynNetIoOperation> spAsynIoOperation;
                    m_spAsynNetwork->CreateAsynIoOperation(m_spAsynFrame, m_af, 0, IID_IAsynNetIoOperation, (IUnknown **)&spAsynIoOperation);
                    m_arOp2AsynTcpSockets[spAsynIoOperation] = spNewAsynTcpSocket;

                    unsigned char *lpBuffer;
                    spAsynIoOperation->NewIoBuffer(0, 0, 0, 0, PER_DATA_SIZE, &lpBuffer);
                    sprintf_s((char *)lpBuffer, 10, "1%08d", m_lSeqno ++);
                    spAsynIoOperation->SetIoParams(0, 10, 0);
                    spNewAsynTcpSocket->Write(spAsynIoOperation);
                }

                {
                    //recv
                    CComPtr<IAsynNetIoOperation> spAsynIoOperation;
                    m_spAsynNetwork->CreateAsynIoOperation(m_spAsynFrame, m_af, 0, IID_IAsynNetIoOperation, (IUnknown **)&spAsynIoOperation);
                    m_arOp2AsynTcpSockets[spAsynIoOperation] = spNewAsynTcpSocket;

                    spAsynIoOperation->NewIoBuffer(0, 0, 0, 0, PER_DATA_SIZE, 0);
                    spAsynIoOperation->SetIoParams(0, 10, 0);
                    spNewAsynTcpSocket->Read(spAsynIoOperation);
                }

                return m_spAsynTcpSocketListener->Accept(lpAsynIoOperation);
            }
        }
        return E_NOTIMPL;
    }

public:
    bool Start(handle pctx, STRING *certandpasswd, PORT port)
    {
        CComPtr<IAsynTcpSocketListener> spAsynInnSocket;
        m_spAsynNetwork->CreateAsynTcpSocketListener(0, &spAsynInnSocket);

        if( m_spAsynNetwork->CreateAsynPtlSocket(STRING_from_string("ssl"), spAsynInnSocket, 0, STRING_from_string("tls/1.0"), &m_spAsynPtlSocket) != S_OK )
        {
            printf("can't load plugin: ssl\n");
            return false;
        }

        CComPtr<ISsl> spSsl;
        m_spAsynPtlSocket->QueryInterface(IID_ISsl, (void **)&spSsl);
        spSsl->SetCryptContext(0, pctx, pctx? 0 : certandpasswd);

        m_spAsynPtlSocket->QueryInterface(IID_IAsynTcpSocketListener, (void **)&m_spAsynTcpSocketListener);
        m_spAsynTcpSocketListener->Open(m_spAsynFrameThread, m_af, SOCK_STREAM, IPPROTO_TCP);

        HRESULT r1 = m_spAsynTcpSocketListener->Bind(asynsdk::STRING_EX::null, port, TRUE, NULL); //???bind
        if( r1 != S_OK)
        {
            printf("bind *:%d, error: %d\n", port, r1);
            return false;
        }

        if( port == 0 ) m_spAsynTcpSocketListener->GetSockAddress(0, 0, &port, 0);
        printf("tcp.listen *:%d\n", port);

        CComPtr<IAsynNetIoOperation> spAsynIoOperation;
        m_spAsynNetwork->CreateAsynIoOperation(m_spAsynFrame, m_af, 0, IID_IAsynNetIoOperation, (IUnknown **)&spAsynIoOperation);
        m_spAsynTcpSocketListener->Accept(spAsynIoOperation);
        return true;
    }

    void Shutdown()
    {
        m_spAsynFrame->Shutdown();
        m_spAsynFrame = NULL;
    }

public:
    CComPtr<IAsynFrameThread> m_spAsynFrameThread;
    CComPtr<IAsynFrame      > m_spAsynFrame;
    CComPtr<IAsynNetwork    > m_spAsynNetwork;
    CComPtr<IAsynTcpSocketListener> m_spAsynTcpSocketListener;
    CComPtr<IAsynRawSocket  > m_spAsynPtlSocket;

    uint32_t m_af; //ipv4/ipv6/ipx
    uint32_t m_lSeqno;
    std::map<IAsynIoOperation *, CComPtr<IAsynTcpSocket> > m_arOp2AsynTcpSockets;
};
