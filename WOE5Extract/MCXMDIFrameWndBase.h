#pragma once

#include <Windows.h>
#include <afx.h>
#include <afxwin.h>

#include "MCXEditBase.h"
#include "MCXStaticBase.h"
#include "MCXButtonBase.h"
#include "MCXListCtrlBase.h"
#include "MCXSpinButtonCtrlBase.h"
#include "MCXCComboBoxBase.h"
#include "MCXCToolTipCtrlBase.h"
#include "MCXMenuBase.h"
#include "MCXNCColor.h"
#include "MCXStatusBarBase.h"
#include "MCXToolBarBase.h"

//
/////////////////////////////////////////////////////////////////////////////
// Boîte de dialogue CMCXMDIFrameWndBase
//
/////////////////////////////////////////////////////////////////////////////
class CMCXMDIFrameWndBase : public CMDIFrameWnd
{
        DECLARE_DYNCREATE(CMCXMDIFrameWndBase)

    public:
        CMCXMDIFrameWndBase();   // constructeur standard
        virtual ~CMCXMDIFrameWndBase();

        CToolTipCtrl    *GetToolTipCtrl();
        BOOL IsValid()
        {
            return m_bValid;
        }
        
        //
        void SetContextMenu ( CMCXMenuBase *pMenu );
        void HandleStatusBar ( CMCXStatusBarBase *pStatusBar );

    protected:  // membres incorporés de la barre de contrôle
	    CMCXToolBarBase         m_wndToolBar;
	    CMCXStatusBarBase       m_wndStatusBar;

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
        CMCXMenuBase            m_AppMenu;
        CMCXMenuBase            m_MdiMenu;

        //  Handle Npn Client
        CMCXNCColor             m_NC;

        BOOL                    m_bValid;

    public :
        CMenu* MDISetMenu( CMenu* pFrameMenu, CMenu* pWindowMenu);

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
       
        afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
        virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
};
