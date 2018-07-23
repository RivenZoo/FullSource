//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_TIMER_H_
#define _ENGINE_TIMER_H_

class ENGINE_API KTimer
{
private:
	#ifdef WIN32
		LARGE_INTEGER	m_nFrequency;
		LARGE_INTEGER	m_nTimeStart;
		LARGE_INTEGER	m_nTimeStop;
	#else
		timeval m_nTimeStart;
		timeval m_nTimeStop;
	#endif
	int				m_nFPS;
public:
	KTimer();
	void			Start();
	void			Stop();
	unsigned int	GetElapse();
	unsigned int	GetElapseMicrosecond();
	unsigned int	GetElapseFrequency();
	unsigned int	GetInterval();
	int				Passed(int nTime);	//返回布尔值
	int				GetFPS(int* nFPS);	//返回布尔值
};

#endif	//_ENGINE_TIMER_H_
