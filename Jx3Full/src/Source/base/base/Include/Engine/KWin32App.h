//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	KWin32App Class
//---------------------------------------------------------------------------
#ifndef _ENGINE_WIN32APP_H_
#define _ENGINE_WIN32APP_H_

//---------------------------------------------------------------------------
class ENGINE_API KWin32App
{
public:
	KWin32App();
	virtual int		Init(HINSTANCE hInstance, const char* AppName, int nIconId);
	virtual void	Run();
	virtual	void	ShowMouse(int bShow);
	LRESULT			MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HWND		GetMainWnd();
public:
	void			SetMouseHoverTime(unsigned int uHoverTime);

protected:
	char	m_szClass[128];
	char	m_szTitle[128];
	int		m_bShowMouse;
	int		m_bActive;

	unsigned int	m_dwMinimizeMainWinTime;	//最小化主窗口的时间
	HWND			m_hWnd;

	virtual	int		InitClass(HINSTANCE hInstance);
	virtual	int		InitWindow(HINSTANCE hInstance);
	virtual int		GameLoop();
	virtual int		HandleInput(UINT uMsg, WPARAM wParam, LPARAM lParam) { return 0; }
private:
	void			GenerateMsgHoverMsg();
	unsigned int	m_uMouseHoverTimeSetting;
	unsigned int	m_uMouseHoverStartTime;
	int				m_nLastMousePos;
	unsigned int	m_uLastMouseStatus;
	int				m_nIconId;
	
};

#endif //_ENGINE_WIN32APP_H_
