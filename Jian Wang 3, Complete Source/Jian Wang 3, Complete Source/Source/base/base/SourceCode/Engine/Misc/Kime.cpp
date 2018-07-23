//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2002 by Kingsoft
//
// File:	KIme.cpp
// Date:	2002.07.18
// Code:	李学武,wooy
// Desc:	KIme Class
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "Kime.h"
#include "KWin32App.h"

ENGINE_API KIme* KIme::ms_pSelf = NULL;

//----------------------------------------------------------------------------
//构造函数，初始化成员
//----------------------------------------------------------------------------
KIme::KIme()
{
    ms_pSelf = this;
	m_bIsWorking=TRUE;
	m_bNoLanguageChange=FALSE;
    m_bCloseFlag = false; 
    m_bCloseFlagForCanChange = false;
    m_dwConversion = 0;
    m_dwSentence = 0;
    m_bCloseIMESimHotKey = false;
    m_nCaretX = 0;
    m_nCaretY = 0;
}

//----------------------------------------------------------------------------
//析构函数，释放内存
//----------------------------------------------------------------------------
KIme::~KIme()
{
	if (ms_pSelf == this)
		ms_pSelf = NULL;
}

//----------------------------------------------------------------------------
//复位IME
//----------------------------------------------------------------------------
void KIme::ResetIme(void)
{
	m_bIsWorking=TRUE;
	m_bNoLanguageChange=FALSE;
}

int KIme::IsIme()
{
	HIMC hImc = ImmGetContext(KWin32App::GetMainWnd());
	int bRet = FALSE;
	if (hImc)
	{
		bRet = (ImmGetOpenStatus(hImc));
		ImmReleaseContext(KWin32App::GetMainWnd(), hImc);
	}
	return bRet;
//	return (ImmIsIME( GetKeyboardLayout(0)));
}

//----------------------------------------------------------------------------
//打开中文输入进入中文状态
//----------------------------------------------------------------------------
void KIme::OpenIME()
{
	HIMC hImc = ImmGetContext(KWin32App::GetMainWnd());
	if (hImc)
	{
		if (ImmGetOpenStatus(hImc) == FALSE)
		{
			bool bOld = m_bNoLanguageChange;
			m_bNoLanguageChange = false;
			ImmSetOpenStatus(hImc, TRUE);
			m_bNoLanguageChange = bOld;
			HWND hWnd = ImmGetDefaultIMEWnd(::KWin32App::GetMainWnd());
			::SendMessage(hWnd, WM_IME_CONTROL, IMC_OPENSTATUSWINDOW, 0);
		}
        if (m_bCloseFlag)
        {
            ImmSetConversionStatus(hImc, m_dwConversion, m_dwSentence);
        }

        int nScreenX = GetSystemMetrics(SM_CXSCREEN);
        int nScreenY = GetSystemMetrics(SM_CYSCREEN);

        POINT ptWindowPos = {0, 0}; 
        //ImmGetStatusWindowPos(hImc, &ptWindowPos);

		//ImmNotifyIME(hImc, NI_CLOSECANDIDATE, 0, 0);
		//ImmNotifyIME(hImc, NI_OPENCANDIDATE, 0, 0);


//        if (
//            !(
//                (ptWindowPos.x >= 0) &&
//                (ptWindowPos.x <= nScreenX) &&
//                (ptWindowPos.y >= 0) &&
//                (ptWindowPos.y <= nScreenY)
//            )
//        )
        {
            ptWindowPos.x =  nScreenX - 100;
            ptWindowPos.y =  nScreenY - 50;
            //ImmSetStatusWindowPos(hImc, &ptWindowPos);
        }

		ImmReleaseContext(KWin32App::GetMainWnd(), hImc);
	}

	if (m_bCloseIMESimHotKey)
    {
        //  这种方法在处理非标准法时都会出现问题
	    if(!ImmIsIME( GetKeyboardLayout( 0 )))
	    {
		    ImmSimulateHotKey(KWin32App::GetMainWnd(),IME_CHOTKEY_IME_NONIME_TOGGLE);
	    }

        m_bCloseIMESimHotKey = false;
    }

    m_bCloseFlag = false;
}

//----------------------------------------------------------------------------
//关闭中文输入进入英文状态
//----------------------------------------------------------------------------
void KIme::CloseIME()
{
    m_bCloseFlag = true;
    m_bCloseFlagForCanChange = true;

    HIMC hImc = ImmGetContext(KWin32App::GetMainWnd());
	if (hImc)
	{
		if (ImmGetOpenStatus(hImc))
		{
			bool bOld = m_bNoLanguageChange;
			m_bNoLanguageChange = false;
			ImmSetOpenStatus(hImc, FALSE);
			m_bNoLanguageChange = bOld;
			HWND hWnd = ImmGetDefaultIMEWnd(::KWin32App::GetMainWnd());
			//::SendMessage(hWnd, WM_IME_CONTROL, IMC_CLOSESTATUSWINDOW, 0);
			ImmGetConversionStatus(hImc, (DWORD*)&m_dwConversion, (DWORD*)&m_dwSentence);
		}
        ImmSetConversionStatus(hImc, IME_CMODE_CHARCODE, IME_SMODE_NONE);

		ImmReleaseContext(KWin32App::GetMainWnd(), hImc);
	}

//  两种方法在处理非标准输入法时会出现问题`
	//while(ImmIsIME( GetKeyboardLayout( 0 )))
	//	ActivateKeyboardLayout(( HKL )HKL_NEXT, 0 );
	//if(ImmIsIME( GetKeyboardLayout( 0 )))
	//{
	//	ImmSimulateHotKey(KWin32App::GetMainWnd(),IME_CHOTKEY_IME_NONIME_TOGGLE);
    //    m_bCloseIMESimHotKey = true;
	//}
}

//----------------------------------------------------------------------------
//停止对消息的响应，暂停工作
//----------------------------------------------------------------------------
void KIme::TurnOff()
{
	m_bIsWorking=FALSE;
}

//----------------------------------------------------------------------------
//恢复对消息的响应，开始工作
//----------------------------------------------------------------------------
void KIme::TurnOn()
{
	m_bIsWorking=TRUE;
}

//----------------------------------------------------------------------------
//允许语言切换
//----------------------------------------------------------------------------
void KIme::EnableLanguageChange()
{
	m_bNoLanguageChange = false;
    m_bCloseFlagForCanChange = false;
}

//----------------------------------------------------------------------------
//禁止语言切换
//----------------------------------------------------------------------------
void KIme::DisableLanguageChange()
{
	m_bNoLanguageChange=TRUE;
}

void KIme::SetCaretPos(int X, int Y)
{
    //if (m_bCloseFlag)
    //    return;

    int bRetCode = false;

    //if (
    //    (m_nCaretX == X) &&
    //    (m_nCaretY == Y)
    //)
    //    return;

    m_nCaretX = X;
    m_nCaretY = Y;

	HIMC hImc = ImmGetContext(KWin32App::GetMainWnd());
	if (hImc)
	{
        COMPOSITIONFORM cf;

        //cf.dwStyle = CFS_POINT;

        //bRetCode = ImmGetCompositionWindow(hImc, &cf);
        //if (bRetCode)
        //{
            cf.dwStyle = CFS_POINT;
            cf.ptCurrentPos.x = m_nCaretX;
            cf.ptCurrentPos.y = m_nCaretY;
            ImmSetCompositionWindow(hImc, &cf);

			//CANDIDATEFORM cdf;
            //
			//cdf.dwStyle = CFS_CANDIDATEPOS;
			//cdf.dwIndex = 0;
			//cdf.ptCurrentPos.x = m_nCaretX;
			//cdf.ptCurrentPos.y = m_nCaretY;
			//ImmSetCandidateWindow(hImc, &cdf);

        //}

        ImmReleaseContext(KWin32App::GetMainWnd(), hImc);
    }


}

//----------------------------------------------------------------------------
//消息处理函数
//----------------------------------------------------------------------------
int	KIme::WndMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_bIsWorking)
	{
		if (uMsg == WM_INPUTLANGCHANGEREQUEST)
        {
            //if (m_bCloseFlag)
            //{
            //    return true;

                //if (m_bCloseFlagForCanChange)
                //{
                //    m_bCloseFlagForCanChange = false;
                //    return true;
                //}
                //
                //return false;
            //}

            if (!m_bNoLanguageChange)
            {
				// 如果允许切换输入法
                DefWindowProc(hWnd, uMsg, wParam, lParam);
                
				SetCaretPos(m_nCaretX, m_nCaretY);

				return true;
            }

			return m_bNoLanguageChange;
        }

		else if (uMsg == WM_IME_NOTIFY)
        {
            if (
                (wParam == IMN_SETOPENSTATUS) &&
                m_bNoLanguageChange
            )
            {
                CloseIME();
                return true;
            }
            else if (wParam  == IMN_SETCONVERSIONMODE)
            {
                
                if (m_bNoLanguageChange)
                {
					static bool s_nInFlag = false;

					if (s_nInFlag)
						return false;
					
					s_nInFlag = true;

                    unsigned int dwConversion = IME_CMODE_CHARCODE;
                    unsigned int dwSentence = IME_SMODE_NONE;
                    HIMC hImc = ImmGetContext(KWin32App::GetMainWnd());
	                if (hImc)
	                {
                        ImmGetConversionStatus(hImc, (DWORD*)&dwConversion, (DWORD*)&dwSentence);
                        
                        //if (
                        //    (dwConversion != IME_CMODE_CHARCODE) || 
                        //    (dwSentence != IME_SMODE_NONE)
                        //)
                        //{
                        //    ImmSetConversionStatus(hImc, IME_CMODE_CHARCODE, IME_SMODE_NONE);
                        //}

		                ImmReleaseContext(KWin32App::GetMainWnd(), hImc);
	                }

					s_nInFlag = false;
                }
                return false;
            }

		}
	}
	return FALSE;
}

