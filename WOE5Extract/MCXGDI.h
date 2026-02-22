#pragma once

#include <Windows.h>
#include "afxwin.h"

class CMCXPen : public CPen
{
    public :
        virtual ~CMCXPen()
        {
            if ( this->m_hObject != NULL )
            {
                DeleteObject ();
            }
        }
};

class CMCXBrush : public CBrush
{
    public :
        virtual ~CMCXBrush()
        {
            if ( this->m_hObject != NULL )
            {
                DeleteObject ();
            }
        }
};

class CMCXBitmap: public CBitmap
{
    public :
        virtual ~CMCXBitmap()
        {
            if ( this->m_hObject != NULL )
            {
                DeleteObject ();
            }
        }
};

