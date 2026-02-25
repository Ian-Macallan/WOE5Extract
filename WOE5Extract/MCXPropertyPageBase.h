#pragma once

#include "resource.h"

#include "afxdlgs.h"

#include "MCXEditBase.h"
#include "MCXStaticBase.h"
#include "MCXButtonBase.h"
#include "MCXListCtrlBase.h"
#include "MCXSpinButtonCtrlBase.h"
#include "MCXCComboBoxBase.h"
#include "MCXCToolTipCtrlBase.h"
#include "MCXMenuBase.h"

//
/////////////////////////////////////////////////////////////////////////////
// Dialog Box CMCXPropertyPageBase
//
/////////////////////////////////////////////////////////////////////////////
class CMCXPropertyPageBase : public CPropertyPage
{
    DECLARE_DYNAMIC(CMCXPropertyPageBase)

    public:
        CMCXPropertyPageBase(UINT code);
        virtual ~CMCXPropertyPageBase();

    // Dialog Box data
    protected :
        CMCXCToolTipCtrlBase    m_ToolTip;
        BOOL                    m_bToolTip;

        CFont                   *m_pBoldFont;
        CFont                   *m_pItalicFont;
        CFont                   *m_pNormalFont;
        CFont                   *m_pFixedFont;
        CFont                   *m_pFixedBoldFont;

        bool                    m_bInitDone;

        CMCXMenuBase            *m_pContextMenu;

    public :

        virtual BOOL NotifyChanges ( ) { return FALSE; };

        void SetContextMenu ( CMCXMenuBase *pMenu );

        //
        virtual void SetThemeChanged ( bool bDarkTheme );

    protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV  Handling

        DECLARE_MESSAGE_MAP()
    public:
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

        virtual BOOL OnInitDialog();

};
