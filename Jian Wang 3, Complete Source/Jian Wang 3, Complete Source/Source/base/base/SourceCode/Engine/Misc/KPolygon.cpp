//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2002.01.10
// Code:	Spe
// Desc:	Polygon Functions
//---------------------------------------------------------------------------
#include "Precompile.h"
#include "KPolygon.h"

KPolygon::KPolygon()
{
	memset(&m_Polygon, 0, sizeof(m_Polygon));
}

int KPolygon::IsPointInPolygon(int x, int y)
{
	int				nXPos[defMaxVertex + 1];
	int				nYPos[defMaxVertex + 1];
	int				bRet = TRUE;
	int				nFlag[2];
	int				nResult;
	register int	i;
	
	for (i = 0; i < m_Polygon.nVertex; i++)
	{
		nXPos[i] = m_Polygon.nXPos[i] - x;
		nYPos[i] = m_Polygon.nYPos[i] - y;
	}
	nXPos[m_Polygon.nVertex] = nXPos[0];
	nYPos[m_Polygon.nVertex] = nYPos[0];
	nFlag[1] = 0;
	for (i = 0; i < m_Polygon.nVertex; i++)
	{
		nResult = nXPos[i] * nYPos[i + 1] - nXPos[i + 1] * nYPos[i];
		nFlag[0]=(nResult>0)?1:((nResult<0)?-1:0);
		if (nFlag[0])
		{
			if (!nFlag[1])
			{
				nFlag[1] = nFlag[0];
			}
			if (nFlag[0] != nFlag[1])
			{
				bRet = FALSE;
				break;
			}
		}
	}
	return bRet;
}


int KPolygon::GetNearVertex(int XPos, int YPos)
{
	int i;
	int	nMin = 0x7fffffff;
	int	nIndex;

	for (i = 0; i < m_Polygon.nVertex; i++)
	{
		if ((m_Polygon.nXPos[i] - XPos) * (m_Polygon.nXPos[i] - XPos) + (m_Polygon.nYPos[i] - YPos) * (m_Polygon.nYPos[i] - YPos) < nMin)
		{
			nIndex = i;
			nMin = (m_Polygon.nXPos[i] - XPos) * (m_Polygon.nXPos[i] - XPos) + (m_Polygon.nYPos[i] - YPos) * (m_Polygon.nYPos[i] - YPos);
		}
	}
	return nIndex;
}

int KPolygon::GetIndexVertex(int i, int* pXPos, int* pYPos)
{
	if (i >= m_Polygon.nVertex)
		return FALSE;
	*pXPos = m_Polygon.nXPos[i];
	*pYPos = m_Polygon.nYPos[i];
	return TRUE;
}

int KPolygon::RemoveIndexVertex(int index)
{
	if (m_Polygon.nVertex < 4)
		return FALSE;

	m_Polygon.nVertex --;
	for (int i = index; i < defMaxVertex - 1; i++)
	{
		m_Polygon.nXPos[i] = m_Polygon.nXPos[i+1];
		m_Polygon.nYPos[i] = m_Polygon.nYPos[i+1];
	}
	return TRUE;
}

int KPolygon::AddPointToVertex(int x, int y)
{
	int nPrevIndex, nNextIndex;
	
	if (m_Polygon.nVertex < 3)
	{
		m_Polygon.nXPos[m_Polygon.nVertex] = x;
		m_Polygon.nYPos[m_Polygon.nVertex] = y;
		m_Polygon.nVertex++;
		return TRUE;
	}
	
	if (m_Polygon.nVertex >= defMaxVertex)
		return FALSE;
	//-------------------------------------------------------------------
	// Add Point to Polygon Last point First
	int		nXPos[2];
	int		nYPos[2];
	int		nResult, nFlag[2];

	m_Polygon.nXPos[m_Polygon.nVertex] = x;
	m_Polygon.nYPos[m_Polygon.nVertex] = y;
	nFlag[1] = 0;
	for (int i = 0; i < m_Polygon.nVertex + 1; i++)
	{
		nPrevIndex = i - 1;
		if (nPrevIndex < 0)
			nPrevIndex = m_Polygon.nVertex;
		nNextIndex = i + 1;
		if (nNextIndex > m_Polygon.nVertex)
			nNextIndex = 0;
		// Get Vector of point to next point
		nXPos[0] = m_Polygon.nXPos[nNextIndex] - m_Polygon.nXPos[i];
		nYPos[0] = m_Polygon.nYPos[nNextIndex] - m_Polygon.nYPos[i];
		// Get Vector of point to previous point
		nXPos[1] = m_Polygon.nXPos[nPrevIndex] - m_Polygon.nXPos[i];
		nYPos[1] = m_Polygon.nYPos[nPrevIndex] - m_Polygon.nYPos[i];
		
		nResult = nXPos[0] * nYPos[1] - nXPos[1] * nYPos[0];
		nFlag[0] = (nResult > 0)?1:((nResult < 0)?-1:0);
		if (nFlag[0])
		{
			if (!nFlag[1])
			{
				nFlag[1] = nFlag[0];
			}
			if (nFlag[0] != nFlag[1])
			{
				m_Polygon.nXPos[m_Polygon.nVertex] = 0;
				m_Polygon.nYPos[m_Polygon.nVertex] = 0;
				return FALSE;
			}
		}
	}
	//-------------------------------------------------------------------
	m_Polygon.nVertex++;
	return TRUE;
}


void KPolygon::LoopVertex(int nTurn)
{
	if (nTurn > m_Polygon.nVertex)
		return;
	if (nTurn < 0)
		nTurn = m_Polygon.nVertex + nTurn;
	int	nNext;

	int		nXBackPos[defMaxVertex];
	int		nYBackPos[defMaxVertex];

	memcpy(nXBackPos, m_Polygon.nXPos, sizeof(m_Polygon.nXPos));
	memcpy(nYBackPos, m_Polygon.nYPos, sizeof(m_Polygon.nYPos));
	
	for (int j = 0; j < m_Polygon.nVertex; j++)
	{
		nNext = j + nTurn;
		if (nNext >= m_Polygon.nVertex)
			nNext -= m_Polygon.nVertex;
		m_Polygon.nXPos[j] = nXBackPos[nNext];
		m_Polygon.nYPos[j] = nYBackPos[nNext];
	}
}

void KPolygon::Clear()
{
	memset(&m_Polygon, 0, sizeof(m_Polygon));	
}

void KPolygon::GetCenterPos(int* pXPos, int* pYPos)
{
	*pXPos = 0;
	*pYPos = 0;
	if (m_Polygon.nVertex)
	{
		for (int i = 0; i < m_Polygon.nVertex; i++)
		{
			*pXPos += m_Polygon.nXPos[i];
			*pYPos += m_Polygon.nYPos[i];
		}
		*pXPos /= m_Polygon.nVertex;
		*pYPos /= m_Polygon.nVertex;
	}
}

int KPolygon::ShiftVertex(int nDir, int nDistance)
{
	int	i;

	switch(nDir)
	{
	case 0:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nYPos[i] += nDistance;
		}
		break;
	case 1:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] -= nDistance;
			m_Polygon.nYPos[i] += nDistance;
		}
		break;
	case 2:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] -= nDistance;
		}
		break;
	case 3:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] -= nDistance;
			m_Polygon.nYPos[i] -= nDistance;
		}
		break;
	case 4:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nYPos[i] -= nDistance;
		}
		break;
	case 5:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] += nDistance;
			m_Polygon.nYPos[i] -= nDistance;
		}
		break;
	case 6:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] += nDistance;
		}
		break;
	case 7:
		for (i = 0; i < m_Polygon.nVertex; i++)
		{
			m_Polygon.nXPos[i] += nDistance;
			m_Polygon.nYPos[i] += nDistance;
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

int KPolygon::GetLeftVertex()
{
	int		nLeft = m_Polygon.nXPos[0];
	int		nIdx = 0;

	for (int i = 1; i < m_Polygon.nVertex; i++)
	{
		if (m_Polygon.nXPos[i] < nLeft)
		{
			nLeft = m_Polygon.nXPos[i];
			nIdx = i;
		}
	}
	return nIdx;
}

int KPolygon::GetRightVertex()
{
	int		nRight = m_Polygon.nXPos[0];
	int		nIdx = 0;
	
	for (int i = 1; i < m_Polygon.nVertex; i++)
	{
		if (m_Polygon.nXPos[i] > nRight)
		{
			nRight = m_Polygon.nXPos[i];
			nIdx = i;
		}
	}
	return nIdx;
}

