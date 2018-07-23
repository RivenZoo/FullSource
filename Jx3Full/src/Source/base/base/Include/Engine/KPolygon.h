//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2002.01.10
// Code:	Spe
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef __ENGINE_POPYGON_H__
#define __ENGINE_POPYGON_H__

#define	defMaxVertex	8
typedef struct
{
	int		nVertex;
	int		nXPos[defMaxVertex];
	int		nYPos[defMaxVertex];
}TPolygon, *LPPolygon;

class ENGINE_API KPolygon  
{
private:
	TPolygon	m_Polygon;
public:
	KPolygon();
	int			IsPointInPolygon(int x, int y);					//	检查当前点是否在多边形内
	int			AddPointToVertex(int x, int y);					//	增加顶点
	int			GetNearVertex(int XPos, int YPos);				//	取得与当前点最近的顶点索引
	int			GetVertexNumber() {return m_Polygon.nVertex;};	//	取得多边形的顶点数目
	int			GetIndexVertex(int i, int* pXPos, int* pYPos);	//	取得多边形的第I个顶点座标
	int			RemoveIndexVertex(int i);						//	从多边形中去除掉一个顶点
	void		LoopVertex(int i);								//	把多边形顶点顺序进行I次循环变化
	void		Clear();										//	清空多边形信息
	void		GetCenterPos(int* pXPos, int* pYPos);			//	取得重心位置
	LPPolygon	GetPolygonPtr() {return &m_Polygon;};			//	取得多边形指针
	int			ShiftVertex(int nDir, int nDistance);			//	把任意顶点向什么方向移动
	int			GetLeftVertex();								//	取得最左顶点的索引
	int			GetRightVertex();								//	取得最右顶点的索引
};

#endif	//__ENGINE_POPYGON_H__

