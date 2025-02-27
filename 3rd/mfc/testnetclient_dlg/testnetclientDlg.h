
// testnetclientDlg.h : 头文件
//

#pragma once

#include <frame/AsynNetwork.h>

// CtestnetclientDlg 对话框
class CtestnetclientDlg : public CDialogEx
{
    // 构造
public:
    CtestnetclientDlg(CWnd *pParent = NULL);	// 标准构造函数

    // 对话框数据
    enum { IDD = IDD_TESTNETCLIENT_DIALOG };

    IThreadMessagePump *CreateThreadMessagePump(InstancesManager *lpInstancesManager)
    {
        return asynsdk::CreateThreadMessagePump(lpInstancesManager, asynsdk::TC_Windows, 0, (IAsynFrameThread**)&m_spAsynFrameThread);
    }

protected:
    virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV 支持

    // 重写
    virtual BOOL ContinueModal();
    virtual void EndModalLoop(int nResult);

    // 实现
protected:
    HICON m_hIcon;

    CComPtr<IAsynFrameThread> m_spAsynFrameThread; //当前线程对应的IAsynFrameThread对象

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
};
