#pragma once
#include "afxwin.h"

//  Menu Indicator
#define ID_MNU_MASK         0xff

#define ID_TOP_MENU         0x00
#define ID_MDI_MENU         0x10
#define ID_SYS_MENU         0x80
#define ID_POP_MENU         0xA0

//
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class CMCXMenuBase : public CMenu
{
    DECLARE_DYNCREATE(CMCXMenuBase)

    public:
        CMCXMenuBase(void);
        virtual ~CMCXMenuBase(void);

        static void InitIcons();

        //
        static void SetOwnDraw ( HMENU hMenu, bool bOwnDrawn = true, int level = 0 );
        static void SetOwnDraw ( CMenu *pMenu, bool bOwnDrawn = true, int level = 0 );

        int         m_iBitmapWidth;
        int         m_iBitmapHeight;

        //
        virtual BOOL CreateMenu();
        virtual BOOL CreatePopupMenu();

        //  Entry Point for Popup Menu
        virtual BOOL LoadMenu(LPCTSTR lpszResourceName);
        //  Entry Point for Popup Menu
        virtual BOOL LoadMenu(UINT nIDResource);

        //  Entry Point for System Menu
        CMCXMenuBase *SetSystemMenu(CWnd* pWnd, CMenu* pSysMenu, int level = ID_SYS_MENU );
        void UnSetSystemMenu(CMenu* pSysMenu, int level = ID_SYS_MENU);
        CMCXMenuBase *SetApplicationMenu(CWnd* pWnd, CMenu *pAppMenu, int level = ID_TOP_MENU );
        void UnSetAppMenu(CMenu* pAppMenu, int level = ID_TOP_MENU);

        CMCXMenuBase *GetSubMenu ( int nPos );
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct );
        virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
        virtual BOOL TrackPopupMenu(UINT nFlags, int x, int y, CWnd* pWnd, LPCRECT lpRect = NULL);

        virtual UINT GetMenuItemCount ( );
        virtual BOOL GetMenuItemInfo ( UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos = FALSE );
        virtual BOOL SetMenuItemInfo ( UINT uItem, LPMENUITEMINFO lpMenuItemInfo, BOOL fByPos = FALSE );
        virtual UINT EnableMenuItem ( UINT nIDEnableItem, UINT nEnable );

        static void MeasureMenuItem ( CDC *pDC, const TCHAR *pText, CSize *pSize );
        void        MeasureMenuItem ( LPMEASUREITEMSTRUCT lpMeasureItemStruct );
        static void DrawMenuItem (  LPDRAWITEMSTRUCT lpDrawItemStruct, CDC *pDC, CRect *pRect, const TCHAR *pText,
                                    MENUITEMINFO *menuInfo );
        void        DrawMenuItem ( LPDRAWITEMSTRUCT lpDrawItemStruct );

        void        ComputeBitmapMaxSize ( );
        void        ComputeBitmapMaxSize ( HBITMAP hBitmap );
        void        DrawBitmap ( CDC *pDC, CBitmap *pBitmap, CRect *pRect );
        int         DrawBitmap(LPDRAWITEMSTRUCT lpDrawItemStruct );
        BOOL        SetMenuItemBitmaps ( UINT nPosition, UINT nFlags, const CBitmap *pBmpUnchecked, const CBitmap *pBmpChecked );

    protected :
        CWnd            *m_pWnd;
        CMenu           *m_pMenu;

        static HICON    m_hCheckWhiteIcon;
        static HICON    m_hCheckBlackIcon;
};

