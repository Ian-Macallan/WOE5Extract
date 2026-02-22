#pragma once

#include <Windows.h>
#include <afx.h>
#include <afxwin.h>
#include <afxcview.h>

#include "MCXEditBase.h"
#include "MCXStaticBase.h"
#include "MCXButtonBase.h"
#include "MCXListCtrlBase.h"
#include "MCXSpinButtonCtrlBase.h"
#include "MCXCComboBoxBase.h"
#include "MCXCToolTipCtrlBase.h"
#include "MCXMenuBase.h"
#include "MCXNCColor.h"

//
/////////////////////////////////////////////////////////////////////////////
// Boîte de dialogue CMCXTreeViewBase
//
/////////////////////////////////////////////////////////////////////////////
class CMCXTreeViewBase : public CTreeView
{
        DECLARE_DYNAMIC(CMCXTreeViewBase)

    public:
        CMCXTreeViewBase();   // constructeur standard
        virtual ~CMCXTreeViewBase();

        CToolTipCtrl    *GetToolTipCtrl();
        BOOL IsValid()
        {
            return m_bValid;
        }
        
        //
        void SetContextMenu ( CMCXMenuBase *pMenu );

    // Données de boîte de dialogue
    public :    
        CFont                   *m_pBoldFont;
        CFont                   *m_pItalicFont;
        CFont                   *m_pNormalFont;
        CFont                   *m_pFixedFont;
        CFont                   *m_pFixedBoldFont;

    protected :
        CMCXCToolTipCtrlBase    m_ToolTip;
        BOOL                    m_bToolTip;

        bool                    m_bInitDone;
        bool                    m_bFirstTime;

        HICON                   m_hIcon;

        //
        CMCXMenuBase            *m_pMenu;

        //  Handle Npn Client
        CMCXNCColor             m_NC;

        BOOL                    m_bValid;

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

        DECLARE_MESSAGE_MAP()

    public:
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

        virtual BOOL PreTranslateMessage(MSG* pMsg);
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);

        afx_msg BOOL OnNcActivate(BOOL bActive);
        afx_msg void OnNcPaint();
        afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
        afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
        afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
        afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
        afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
        afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
        afx_msg void OnNcMouseHover(UINT nFlags, CPoint point);
        afx_msg void OnNcMouseLeave();
       
        virtual void OnInitialUpdate();
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
