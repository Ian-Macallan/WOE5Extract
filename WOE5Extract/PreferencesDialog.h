#if !defined(AFX_PREFERENCESDIALOG_H__5DF2B5A1_6D56_11D5_A09F_0000E8C97BDE__INCLUDED_)
#define AFX_PREFERENCESDIALOG_H__5DF2B5A1_6D56_11D5_A09F_0000E8C97BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreferencesDialog.h : header file
//
#include <Windows.h>
#include <afx.h>
#include <afxcmn.h>

#include "MsgFmtComboBox.h"
#include "AttFmtComboBox.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDialog dialog

class CPreferencesDialog : public CDialog
{
// Construction
public:
    CPreferencesDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CPreferencesDialog)
    enum { IDD = IDD_PREFERENCES };
    CButton m_CreateIndexFiles;
    CSpinButtonCtrl m_MRU_Count_Spin;
    CEdit   m_MRU_Count;
    CButton m_Disk_Button;
    CButton m_Dir_Button;
    CButton m_Over;
    CButton m_Att_Over;
    CEdit   m_Att_Extension;
    CEdit   m_Extension;
    CAttFmtComboBox m_MsgFmt_Value_9;
    CAttFmtComboBox m_MsgFmt_Value_8;
    CAttFmtComboBox m_MsgFmt_Value_7;
    CAttFmtComboBox m_MsgFmt_Value_6;
    CAttFmtComboBox m_MsgFmt_Value_5;
    CSpinButtonCtrl m_MsgFmt_Spin_9;
    CSpinButtonCtrl m_MsgFmt_Spin_8;
    CSpinButtonCtrl m_MsgFmt_Spin_7;
    CSpinButtonCtrl m_MsgFmt_Spin_6;
    CSpinButtonCtrl m_MsgFmt_Spin_5;
    CEdit   m_MsgFmt_Size_9;
    CEdit   m_MsgFmt_Size_8;
    CEdit   m_MsgFmt_Size_7;
    CEdit   m_MsgFmt_Size_6;
    CEdit   m_MsgFmt_Size_5;
    CMsgFmtComboBox m_MsgFmt_Value_4;
    CMsgFmtComboBox m_MsgFmt_Value_3;
    CMsgFmtComboBox m_MsgFmt_Value_2;
    CSpinButtonCtrl m_MsgFmt_Spin_4;
    CSpinButtonCtrl m_MsgFmt_Spin_3;
    CSpinButtonCtrl m_MsgFmt_Spin_2;
    CEdit   m_MsgFmt_Size_4;
    CEdit   m_MsgFmt_Size_3;
    CEdit   m_MsgFmt_Size_2;
    CMsgFmtComboBox m_MsgFmt_Value_1;
    CSpinButtonCtrl m_MsgFmt_Spin_1;
    CEdit   m_MsgFmt_Size_1;
    CButton m_AssociateDbx;
    CEdit   m_Directory;
    CEdit   m_DiskDrive;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPreferencesDialog)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    CToolTipCtrl m_ToolTip;
    CString m_ToolTipText;

    // Generated message map functions
    //{{AFX_MSG(CPreferencesDialog)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnDirButton();
    afx_msg void OnDiskButton();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFERENCESDIALOG_H__5DF2B5A1_6D56_11D5_A09F_0000E8C97BDE__INCLUDED_)
